#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include "iocp.h"

using namespace std;

// test loop num, default
int LOOP = 10;
int testType = 1;

DWORD WINAPI iocpClient(LPVOID lpParam) {
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		printf( "Using %s (Status:%s)\n", wsaData.szDescription, wsaData.szSystemStatus ); 
        printf( "with API versions: %d.%d to %d.%d", 
                 LOBYTE( wsaData.wVersion), HIBYTE( wsaData.wVersion ), 
                 LOBYTE( wsaData.wHighVersion), HIBYTE( wsaData.wHighVersion) );

        return -1; 
	} /* else {
		std::cout << "Windows socket 2.2 startup" << std::endl;
	}*/

	// sock
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (!sockSrv) {
		std::cout << "create socket failed" << std::endl;
		goto end;
	}

	SOCKADDR_IN srvAddr;
	srvAddr.sin_addr.S_un.S_addr = inet_addr(SRV_IP);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(PORT);

	// connect
	if (SOCKET_ERROR == connect(sockSrv, (SOCKADDR *)&srvAddr, sizeof(SOCKADDR))) {
		cout << "connect failed." << endl;
		goto end;
	} else {
		std::cout << GetCurrentThreadId() << " connect " << SRV_IP << ":" << PORT << " successfully." << std::endl;
		Sleep(200);
	}

#define MSG_BUFF_SIZE 1024

	char msg[MSG_BUFF_SIZE];

	if (testType == 1) {
		while (true) {
			std::cout << "~$ ";
			std::cin.getline(msg, MSG_BUFF_SIZE, '\n');

			if (!strncmp(msg, "q", 1) || !strncmp(msg, "exit", 4)) {
				std::cout << "exit" << std::endl;
				closesocket(sockSrv);
				goto end;
			}

			int n = send(sockSrv, msg, strlen(msg), 0);
			if (n == 0) {
				std::cout << "send failed." << std::endl;
				closesocket(sockSrv);
				goto end;
			}
		}	
	}
	else if (testType == 2) {
		/// send msg times accroding to loop.
		sprintf_s(msg, "The message was sended by tid:%d.", GetCurrentThreadId());
		for (int i = 0; i < LOOP; i++) {
			send(sockSrv, msg, strlen(msg), 0);
			Sleep(200);
		}
	} 

end:
	WSACleanup();
	return 0;
}

void MultiThreadIO_test() {
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	HANDLE tThreadArray[32];

	const int threadNum = SystemInfo.dwNumberOfProcessors;
	//std::cout << "cpu num: " << threadNum << std::endl;

	for(int i = 0; i < threadNum; i++)
	{
		tThreadArray[i] = CreateThread(NULL, 0, iocpClient, NULL, 0, NULL);
		if(!tThreadArray[i])
			std::cout << "create thread failed." << std::endl;
	}
	
	WaitForMultipleObjects(threadNum, tThreadArray, TRUE, INFINITE); 
}

void Usage() {
	std::cout << "[USAGE]" << std::endl;
	std::cout << "\ttype: 1 - command" << std::endl;
	std::cout << "\t      2 - loop loopnum" << std::endl;
	std::cout << "example: exe 1" << std::endl;
	std::cout << "         exe 2 100" << std::endl;
}

int main(int argc, char **argv) 
{
	if (argc < 2) {
		Usage();
		return -1;
	}

	if (argc == 2 && atoi(argv[1]) == 1) {
			testType = 1;

			iocpClient(NULL);
	} else  if (argc == 3 && atoi(argv[1]) == 2) {
		int param = atoi(argv[1]);
			testType = 2;
			LOOP = atoi(argv[2]);

			MultiThreadIO_test();
	} else {
		Usage();
		return -1;
	}

	return 0;
}