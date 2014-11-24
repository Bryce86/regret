#ifndef __EPOLL_SRV_H__
#define __EPOLL_SRV_H__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 1024
#define MAX_EVENTS 64
#define DEFAULT_PORT "5566"

struct remoteInfo{
	int fd;
	int port;
	std::string ip;
};

class epollService {
public:
	epollService();
	~epollService();
	
	int startServer(int port);
private:
	static int sendMsg(int fd, const std::string& msg); 
	static int sendMsg(struct epoll_event &ev, const std::string& msg); 
	static int recvMsg(int fd);
	static int recvMsg(struct epoll_event &ev);
	static void* WorkerThread(void *arg);

	int createEpoll();
	int addEpoll(int fd);
	int addEpoll(remoteInfo &ri);

	sockaddr_in m_srvAddr;
	int m_lfd; // listen socket
	int m_cfd; // client socket
	static int m_epfd; // epoll fd
};

#endif /* __EPOLL_SRV_H__ */
