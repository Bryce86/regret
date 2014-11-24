#include <iostream>
#include <pthread.h>
#include <cstring>
#include "epService.h"
using namespace std;

int epollService::m_epfd = 0;

epollService::epollService() /*: m_epEvts(NULL)*/ {
/*
	m_epEvts = new epoll_event[MAX_EVENTS];	
	if (!m_epEvts) {
		std::cout << "alloc epoll_event array failed." << std::endl;
	}
*/
}

epollService::~epollService() {
/*
	if (m_epEvts != NULL) {
		delete []m_epEvts;	
		m_epEvts = NULL;
	}
*/
}

int epollService::startServer(int port) {
	std::cout << "start service ..." << std::endl;

	// create epoll fd
	if (createEpoll() < 0)
		return -1;
		
	// create worker thread.
	pthread_t tid = 0;
	if (0 != pthread_create(&tid, NULL, WorkerThread, (void *)&m_epfd))
	{
		std::cout << "pthread_create failed." << std::endl;
		return -1;
	}
	sleep(1);
	std::cout << ">>" << std::endl;
	
	// socket
	bzero(&m_srvAddr, sizeof(m_srvAddr));
	m_srvAddr.sin_family = AF_INET;
	m_srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_srvAddr.sin_port = htons(port);

	m_lfd = socket(AF_INET, SOCK_STREAM, 0);	
	if (m_lfd < 0) {
		std::cout << "create socket failed." << std::endl;	
		return -1;
	}

	// reuse bind
	int flag = 1;
	setsockopt(m_lfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));

	// bind, listen
	if (bind(m_lfd, (struct sockaddr *)&m_srvAddr, sizeof(m_srvAddr)) < 0) {
		std::cout << "bind failed." << std::endl;	
		return -1;
	}
	listen(m_lfd, 100);

	// accpet, epoll add
	while (true) {
		struct sockaddr_in clntAddr;
		socklen_t csLen = sizeof(struct sockaddr_in);
		int clntSock;

		//std::cout << "waiting connect ..." << std::endl;
		if ((clntSock = accept(m_lfd, (struct sockaddr *)&clntAddr, &csLen)) < 0) {
			std::cout << "accept failed (" << clntSock << ")."<< std::endl; 
			continue;
		}		
		std::cout << "accept " << inet_ntoa(clntAddr.sin_addr) << ":" << ntohs(clntAddr.sin_port) << std::endl;

#ifdef USE_REMOTEINFO
		remoteInfo *pri = new(remoteInfo);	
		pri->fd = clntSock;
		pri->ip = inet_ntoa(clntAddr.sin_addr);
		pri->port = ntohs(clntAddr.sin_port);
		addEpoll(*pri);
#else
		addEpoll(clntSock);
#endif
	}

	close(m_lfd);
	return 0;
}

void* epollService::WorkerThread(void *arg) {
	std::cout << "start worker thread(" << pthread_self() << ") ..." << std::endl;

	int epfd = *((int *)arg);
	struct epoll_event epEvts[MAX_EVENTS];
	int nfds = 0;

	while (true) {
		nfds = epoll_wait(epfd, epEvts, MAX_EVENTS, -1);
		for (int i = 0; i < nfds; i++) {
			//std::cout << "event: " << epEvts[i].events << std::endl;

			/*
			if (epEvts[i].data.fd == m_lfd) { // check LISTEN	
			}
			*/
			if (epEvts[i].events & EPOLLIN) {
#ifdef USE_REMOTEINFO
				recvMsg(epEvts[i]); 
#else
				recvMsg(epEvts[i].data.fd);
#endif
			}
			else if (epEvts[i].events & EPOLLOUT) {
				std::cout << "EPOLLOUT" << std::endl;	
			}
			else {
				std::cout << "UNKNOW event." << std::endl;	
			}
		}
	}
}


int epollService::createEpoll() {
	m_epfd = epoll_create(10000);
	if (m_epfd < 0) {
		std::cerr << "epoll_create failed." << std::endl;	
		return -1;
	}
	return 0;
}

int epollService::addEpoll(int fd) {
	struct epoll_event ev;

	ev.data.fd = fd;
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLET; // default EPOLL LT

	if (epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
		std::cerr << "epoll_ctl failed." << std::endl;	
		return -1;
	}
	return 0;
}

int epollService::addEpoll(remoteInfo &ri) {
	struct epoll_event ev;

	ev.data.ptr = &ri;
	//ev.events = EPOLLIN;
	ev.events = EPOLLIN | EPOLLET; // default EPOLL LT

	if (epoll_ctl(m_epfd, EPOLL_CTL_ADD, ri.fd, &ev) < 0) {
		std::cerr << "epoll_ctl failed." << std::endl;	
		return -1;
	}
	return 0;
}

int epollService::sendMsg(int fd, const std::string& msg) {
	//TODO: 
	return 0;
}

int epollService::sendMsg(struct epoll_event &ev, const std::string &msg) {
	//TODO: 
	return 0;
}

int epollService::recvMsg(int fd) {
	char buff[BUFF_SIZE];	
	int rcvLen;

	rcvLen = recv(fd, buff, BUFF_SIZE, 0);
	if (rcvLen < 0) {
		std::cout << "recv failed. len(" << rcvLen << ")" << std::endl;
		return -1;
	}
	else if (rcvLen == 0) {
		std::cout << "client disconnected." << std::endl;

		// epoll del
		epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, NULL); 
		return 1;
	}

	buff[rcvLen] = '\0';
	std::cout << "recv: " <<  buff << " (" << rcvLen << ")" <<  std::endl; 

	return 0;
}

int epollService::recvMsg(struct epoll_event &ev) {
	char buff[BUFF_SIZE];	
	int fd, rcvLen;

	remoteInfo *pri = (remoteInfo *)ev.data.ptr;
	fd = pri->fd;
	//std::cout << "DEBUG: " << pri->ip.c_str() << ":" << pri->port << " fd:" << pri->fd << std::endl;

	rcvLen = recv(fd, buff, BUFF_SIZE, 0);
	if (rcvLen < 0) {
		std::cout << "recv failed. len(" << rcvLen << ") from " 
			      << pri->ip.c_str() 
				  << ":" 
				  << pri->port 
				  << std::endl;
		return -1;
	}
	else if (rcvLen == 0) {
		std::cout << "disconnected from " 
			      << pri->ip.c_str() 
				  << ":" 
				  << pri->port 
				  << std::endl;

		// epoll del
		epoll_ctl(m_epfd, EPOLL_CTL_DEL, pri->fd, NULL);
		// delete remoteInfo
		if (pri) {
			delete pri;	
			pri = NULL;
		}
		return 1;
	}

	buff[rcvLen] = '\0';
	std::cout << "[" << pri->ip.c_str() << ":" << pri->port << "] " <<  buff << std::endl; 

	return 0;
}

int main(int argc, char **argv)
{
	epollService es; 
	es.startServer(5566);

	return 0;
}
















