#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <event.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5566

struct event_base *base;

typedef struct sock_ev {
	struct event* read_ev;
	struct event* write_ev;
	char *buff;
	char ip[18];	
	int port;
}sock_ev;

void release_sock_event(struct sock_ev *ev) {
	event_del(ev->read_ev);
	free(ev->read_ev);
	free(ev->write_ev);
	free(ev->buff);
	free(ev);
}

void onWrite(int sock, short event, void *arg) {
	char *buff = (char *)arg;

	int nwrite = send(sock, buff, strlen(buff), 0);
	if (nwrite <= 0) {
		perror("write");	
	}

	free(buff);
}

void onRead(int sock, short event, void *arg) {
	struct sock_ev *ev = (struct sock_ev *)arg;
	int nread;

	ev->buff = (char *)malloc(BUFSIZ);
	bzero(ev->buff, BUFSIZ);
	nread = recv(sock, ev->buff, BUFSIZ, 0);
	if (nread == 0) {
		release_sock_event(ev);	
		close(sock);
		printf("client disconnect.\n");
		return;
	}
	printf("[%s:%d] %s\n", ev->ip, ev->port, ev->buff);
	
	event_set(ev->write_ev, sock, EV_WRITE, onWrite, ev->buff);
	event_base_set(base, ev->write_ev);
	event_add(ev->write_ev, NULL);
}

void onAccept(int sock, short event, void *arg) {
	struct sockaddr_in remote;	
	socklen_t addrlen = sizeof(struct sockaddr_in);
	int connfd; 

	struct sock_ev *ev = (struct sock_ev *)malloc(sizeof(struct sock_ev));
	ev->read_ev = (struct event *)malloc(sizeof(struct event));
	ev->write_ev = (struct event *)malloc(sizeof(struct event));

	connfd = accept(sock, (struct sockaddr *)&remote, &addrlen);
	if (connfd < 0) {
		perror("accept");	
		return;
	}
	strcpy(ev->ip, inet_ntoa(remote.sin_addr));
	ev->port = ntohs(remote.sin_port);
	printf("accept: %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));

	event_set(ev->read_ev, connfd, EV_READ|EV_PERSIST, onRead, ev);
	event_base_set(base, ev->read_ev);
	event_add(ev->read_ev, NULL);
}

void setReuseAddr(int fd) {
	int flag = 1;

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));
}

int main(int argc, char **argv) 
{
	struct sockaddr_in local;
	int listenfd;

	// socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	setReuseAddr(listenfd);

	bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(PORT);

	bind(listenfd, (struct sockaddr *)&local, sizeof(struct sockaddr));
	listen(listenfd, 100);

	// event
	struct event listen_ev;
	base = event_base_new();
	event_set(&listen_ev, listenfd, EV_READ|EV_PERSIST, onAccept, NULL);
	event_base_set(base, &listen_ev);
	event_add(&listen_ev, NULL);

	event_base_dispatch(base);

	return 0;
}


