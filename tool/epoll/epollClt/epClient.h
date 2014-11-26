#ifndef __EPOLL_CLIENT_H__
#define __EPOLL_CLIENT_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include <pthread.h>

#define LOOP_MSG_NUM 2000 // every thread send LOOP_MSG_NUM messages.
#define PROCESSOR_NUM 8 // create PROCESSOR_NUM threads.

class epollClient {
public:
	epollClient(const std::string ip = "127.0.0.1", int port=5566);
	~epollClient();
	int Connect();
	int Disconnect();
	int sendMsg(const std::string msg);
	int recvMsg();

private:	
	std::string m_ip;
	int m_port;
	int m_fd; // socket
};

#endif /*ifndef __EPOLL_CLIENT_H__ */
