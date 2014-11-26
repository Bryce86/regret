/*
 * Epoll example
 */

#include <sys/socket.h> // SOCK_SUCCESS - 0; SOCK_ERROR - -1
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdio.h> // perror output with '\n'
#include <stdlib.h> // EXIT_FAILURE - 1; EXIT_SUCCESS - 0
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_EVENTS 64
#define PORT 5566

typedef struct _remoteInfo {
	int fd;
	char ip[18];
	int port;
}remoteInfo;

// set non-blocking option
void setnonblocking(int fd) {
	int opts;

	opts = fcntl(fd, F_GETFL);
	if (opts < 0) {
		perror("fcntl(F_GETFL)");	
		exit(EXIT_FAILURE);
	}

	opts |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, opts) < 0) {
		perror("fcntl(F_SETFL)");	
		exit(EXIT_FAILURE);
	}
}

void setReuseAddr(int fd) {
	int flag = 1;

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) != 0) {
		perror("setsockopt");	
		exit(EXIT_FAILURE);
	}
}

int main()
{
	struct epoll_event ev, events[MAX_EVENTS];
	int listenfd, connfd, nfds, epfd, i, nread, n, fd;
	struct sockaddr_in local, remote;
	char buf[BUFSIZ]; // SYSTEM MACRO: 8192
	remoteInfo *pril;
	/*
	 * The addrlen argument is a value-result argument:
	 * the caller must initialize it to contain the size (in byte)
	 * of the structure pointed to by addr; on return it will contain 
	 * the actual size of the peer address.
	 */
	socklen_t addrlen = sizeof(struct sockaddr_in);  

	// socket, bind, listen
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("sockfd");	
		exit(EXIT_FAILURE);
	}

	// set reuseaddr and nonblocking
	setReuseAddr(listenfd);
	setnonblocking(listenfd);

	bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(PORT);
	if (bind(listenfd, (struct sockaddr *)&local, sizeof(local)) < 0) {
		perror("bind");	
		exit(EXIT_FAILURE);
	}
	listen(listenfd, 20);

	// epoll create
	epfd = epoll_create(MAX_EVENTS);
	if (epfd == -1) {
		perror("epoll_create");	
		exit(EXIT_FAILURE);
	}
	
	/*
	 * use user-defined structure
	 * To save the remote side informations (ip & port).
	 */	
	pril = (remoteInfo *)malloc(sizeof(remoteInfo));
	pril->fd = listenfd;
	ev.data.ptr = pril;
	ev.events = EPOLLIN;

	if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
		perror("epoll_ctl: add listen_sock");	
		exit(EXIT_FAILURE);
	}

	for (;;) {
		nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);	
		if (nfds == -1) {
			perror("epoll_wait");	
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < nfds; ++i) {
			// check listen fd, process new connection
			remoteInfo *pri = (remoteInfo *)(events[i].data.ptr);
			fd = pri->fd;

			if (fd == listenfd) {
				while ((connfd = accept(listenfd, (struct sockaddr *)&remote, &addrlen)) > 0) {
					printf("accept: %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
					setnonblocking(connfd);	

					/*
					 * use user-defined structure
					 * if we want to save the performence, reduce the alloc. 
					 * We can define a static remoteInfo array.
					 */
					remoteInfo *p = (remoteInfo *)malloc(sizeof(remoteInfo));
					p->fd = connfd;
					strcpy(p->ip, inet_ntoa(remote.sin_addr));
					p->port = ntohs(remote.sin_port);
					ev.events = EPOLLIN | EPOLLET;
					ev.data.ptr = p;

					if (epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev) == -1) {
						perror("epoll_ctl: add connfd");	
						exit(EXIT_FAILURE);
					}
				}	

				if (connfd == -1) {
					if (errno != EAGAIN && errno != ECONNABORTED 
								&& errno != EPROTO && errno != EINTR)	
					  perror("accept");
				}
				continue;
			}

			// process read fd
			if (events[i].events & EPOLLIN) {
				n = 0;	
				memset(buf, 0x0, BUFSIZ);

				while ((nread = read(fd, buf + n, BUFSIZ-1)) > 0) {
					n += nread;	
				}
				if (nread == -1 && errno != EAGAIN) { // 11 - EAGAIN
					perror("read error");	
				} else if (nread == 0) {
					printf("client disconnected.\n"); 

					if (pri) {
						printf("delete %p\n", pri);
						free(pri);
						pri = NULL;
					}
					continue;
				}
				printf("[%s:%d] %s\n", pri->ip, pri->port, buf);

				/*
				 * whether give a response 
				 * when we read a message from client. And we want to 
				 * response it. Then we modify the fd to EPOLLOUT.
				 * And we receive a write event at once. Code will run
				 * the case at below.
				 */
#if 1 
				// change event to response
				ev.data.ptr = events[i].data.ptr;
				ev.events = events[i].events | EPOLLOUT;

				if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
					perror("epoll_ctl: mod");	
				}
#endif
			}

			// process write fd
			if (events[i].events & EPOLLOUT) {
				memset(buf, 0x0, BUFSIZ);
				sprintf(buf, "200 OK", 7);		
				int nwrite, data_size = strlen(buf);
				n = data_size;

				while (n > 0) {
					nwrite = write(fd, buf + data_size - n, n);	
					if (nwrite < n) {
						if (nwrite == -1 && errno != EAGAIN) {
							perror("write error");	
						}	
						break;
					}
					n -= nwrite;
				}

				/*
				 * When we have sended the message. We must modify the attribute
				 * of fd. Remove the EPOLLOUT, we can receive msg from current client.
				 * If EPOLL_CTL_DEL the fd, it equal to close fd. We disconnect with
				 * client already.
				 */
				ev.data.ptr = events[i].data.ptr;
				ev.events =  EPOLLIN | EPOLLET;

				if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
					perror("epoll_ctl: mod");
				}
				//close(fd); // sevice close socket actively, used to HTTP Response.
			}
		}
	}

	// free
	if (pril) {
		free(pril);
		pril = NULL;
	}
	return 0;
}



