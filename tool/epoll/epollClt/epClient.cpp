#include <iostream>
#include <cstring>
#include "epClient.h"
using namespace std;

epollClient::epollClient(const std::string ip, int port) {
	m_ip = ip;
	m_port = port;
}

epollClient::~epollClient() {
	Disconnect();
}

int epollClient::Connect() {
	struct sockaddr_in remoteAddr;
	remoteAddr.sin_family = AF_INET;
	remoteAddr.sin_addr.s_addr = inet_addr(m_ip.c_str());
	remoteAddr.sin_port = htons(m_port);	

	if ((m_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "create socket failed." << std::endl;	
		return -1;
	}

	if (connect(m_fd, (struct sockaddr *)&remoteAddr, sizeof(struct sockaddr)) < 0) {
		std::cout << "connect "	<< m_ip << ":" << m_port << " failed." << std::endl;
		return -1;
	}
	std::cout << "connect "	<< m_ip << ":" << m_port << " successfully." << std::endl;

	return 0;
}

int epollClient::Disconnect() {
	if (m_fd) {
	std::cout << "disconnet from " << m_ip << ":" << m_port << "." << std::endl; 
		close(m_fd);
		m_fd = 0;
	}
}

int epollClient::sendMsg(const std::string msg) {
	int sndLen = send(m_fd, msg.c_str(), strlen(msg.c_str()), 0);
	if (sndLen <= 0) {
		std::cout << "send failed." << std::endl;	
		return -1;
	}
	return 0;
}

int epollClient::recvMsg() {
	char buff[1024];
	int nread = recv(m_fd, buff, 1024, 0);
	if (nread < 0) {
		std::cout << "recv failed." << std::endl;	
		return -1;
	}
	buff[nread] = '\0';
	std::cout << buff << std::endl;

	return 0;
}

int Singleton() {
	epollClient ec("127.0.0.1", 5566);
	ec.Connect();

	char buff[1024];
	while (true) {
		std::cout << ">> ";
		std::cin.getline(buff, 1024, '\n');

		if (!strcmp(buff, "exit") || !strcmp(buff, "q")) {
			std::cout << buff << std::endl;	
			break;
		}

		if (!strcmp(buff, "reconnect")) {
			ec.Disconnect();
			if (!ec.Connect())	
			  continue;
			else {
				std::cout << "reconnect failed." << std::endl;	
				return -1;
			}
		}

		if (ec.sendMsg(buff) == 0) {
			// if service give a response
			ec.recvMsg();
		}	
	}
}

// sub thread
void * WorkerThread(void *) {
	std::cout << "start thread(" << pthread_self() << ") ..." << std::endl;
	sleep(3); // wait for all threads generated

	epollClient ec("127.0.0.1", 5566);
	ec.Connect();
	for (int i = 0; i < LOOP_MSG_NUM; i++) {
		ec.sendMsg("This is a test msg.");	
		ec.recvMsg();
		//microsecond
		usleep(5 * 1000); // if not waiting, LOOP_MSG_NUM messages all be combined to one.
	}
	ec.Disconnect();
}

int Multiton() {
	pthread_t tidArr[PROCESSOR_NUM];
	int err;

	for (int i = 0; i < PROCESSOR_NUM; i++)	{
		err = pthread_create(&tidArr[i], NULL, WorkerThread, NULL);		
		if (err != 0) {
			std::cout << "create thread failed." << std::endl;	
			return -1;
		}
	}

	for (int i = 0; i < PROCESSOR_NUM; i++) {
		pthread_join(tidArr[i], NULL);	
		std::cout << "end thread(" << tidArr[i] << ") ..." << std::endl;
	}
}

int main(int argc, char **argv)
{
	Singleton();
	//Multiton();
	return 0;
}


