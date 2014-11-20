#include <iostream>
#include <string>
#include <cstdio>
#include "iocp.h"

using namespace std;

// functions declare
DWORD WINAPI WorkerThread(LPVOID lpParam);

int main(int argc, char **argv) {
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		printf( "Using %s (Status:%s)\n", wsaData.szDescription, wsaData.szSystemStatus ); 
        printf( "with API versions: %d.%d to %d.%d", 
                 LOBYTE( wsaData.wVersion), HIBYTE( wsaData.wVersion ), 
                 LOBYTE( wsaData.wHighVersion), HIBYTE( wsaData.wHighVersion) );

        return -1; 
	} else {
		std::cout << "Windows socket 2.2 startup" << std::endl;
	}

	/*
	WINBASEAPI __out HANDLE WINAPI CreateIoCompletionPort(
		__in HANDLE FileHandle,
		__in_opt HANDLE ExistingCompletionPort,
		__in ULONG_PTR CompletionKey,
		__in DWORD NumberOfConcurrentThreads
	);
	
	FileHandle是关联的文件句柄。
	ExistingCompletionPort是已经存在的完成端口。如果为NULL，则为新建一个IOCP。
	CompletionKey是传送给处理函数的参数。
	NumberOfConcurrentThreads是有多少个线程在访问这个消息队列。
							 当参数ExistingCompletionPort不为0的时候，系统忽略该参数。
							 当该参数为0表示允许同时相等数目于处理器个数的线程访问该消息队列。
	*/
	
	
	// 创建工作线程处理完成端口对象的事件
	HANDLE hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (!hIocp) {
		std::cout << "CreateIoCOmpletionPort failed." << std::endl;
		goto end;
	}

	// 获取CPU个数，创建线程池
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	for (DWORD i = 0; i < sysInfo.dwNumberOfProcessors * 2; ++ i) {
		// 创建工作线程，关联到完成端口上
		HANDLE th = CreateThread(NULL, 0, WorkerThread, hIocp, 0, NULL);
		if (!th) {
			std::cout << "Create thread handle failed." << std::endl;
			goto end;
		}
		CloseHandle(th);
	}

	// 创建套接字，绑定，监听
	SOCKET srvSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(srvSock, (sockaddr *)&addr, sizeof(addr)) < 0) {
		std::cout << "bind failed." << std::endl;
		goto end;
	}
	if (listen(srvSock, 20) != 0) {
		std::cout << "listen failed." << std::endl;
		goto end;
	}

	std::cout << "iocp demo start (PORT:" << PORT << ")..." << std::endl;
	
	while (true) {
		SOCKADDR_IN remoteAddr;
		int remoteAddrLen = sizeof(remoteAddr);

		SOCKET sockRemote = accept(srvSock, (sockaddr *)&remoteAddr, &remoteAddrLen);
		std::cout << "accept a connect " << inet_ntoa(remoteAddr.sin_addr) 
			<< ":" << ntohs(remoteAddr.sin_port) << std::endl;

		// 接收到新连接，为其创建以个per_handle结构，并将关联到完成端口对象
		PPER_HANDLE_DATA pPerHandle = (PPER_HANDLE_DATA) GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		if (!pPerHandle) {
			break;
		}
		pPerHandle->s = sockRemote;
		pPerHandle->addr = remoteAddr;
		CreateIoCompletionPort((HANDLE)pPerHandle->s, hIocp, (DWORD)pPerHandle, 0);

		// 投递一个接收请求
		// http://bbs.csdn.net/topics/310134915 
		PPER_IO_DATA pIoData = (PPER_IO_DATA) GlobalAlloc(GPTR, sizeof(PER_IO_DATA));
		if (!pIoData) {
			break;
		}
		
		ZeroMemory(pIoData, sizeof(PER_IO_DATA));
		pIoData->nOperationType = OP_READ;
		pIoData->DataBuf.buf = pIoData->buf;
		pIoData->DataBuf.len = BUFFER_SIZE;

		DWORD dwRecv = 0;
		DWORD dwFlags = 0;
		/*
			WSARecv 只是向系统提交一个异步接收请求，这个请求会在有数据到达之后返回，并且放入完成队列通知工作线程，
			这个异步接收请求到此完成，继续提交请求是为了接收下一个数据包，也就是说，每次请求返回之后必须再次提交。

			类似这样：
			1. 你让一个前台去等待接待一个客人(WSARecv)然后继续做你的事情
			2. 你的秘书会一直等着资料夹有新文件然后拿给你然后继续等待有新文件(loop)
			3. 前台接待客人之后把客户资料放到资料夹之后就不会继续去前台接待客人了
			4. 这个时候如果你不再派前台继续去等待接待客人(WSARecv)，那么你的资料夹不会有新的资料了，
			   这时就需要再次指派前台去等待接待新的客人(再次WSARecv)。
		*/
		WSARecv(pPerHandle->s, &pIoData->DataBuf, 1, &dwRecv, &dwFlags, &pIoData->ol, NULL);
	}

end:
	WSACleanup();
	return 0;
}

DWORD WINAPI WorkerThread(LPVOID lpParam) {
	HANDLE hIocp = (HANDLE)lpParam;
	if (!hIocp)
		return -1;

	DWORD dwTrans = 0;
	PPER_HANDLE_DATA pPerHandle;
	PPER_IO_DATA pIoData;

	while (true) {
		BOOL ret = GetQueuedCompletionStatus(hIocp, &dwTrans, (LPDWORD)&pPerHandle, (LPOVERLAPPED *)&pIoData, WSA_INFINITE);
		if (!ret) {
			if( (GetLastError() == WAIT_TIMEOUT) || (GetLastError() == ERROR_NETNAME_DELETED) )	{
				std::cout << "close socket " << inet_ntoa(pPerHandle->addr.sin_addr)
				          << ":" << ntohs(pPerHandle->addr.sin_port) << std::endl;
			}
			else {
				std::cout << "GetQueuedCompletionStatus failed." << std::endl;
			}

			closesocket(pPerHandle->s);
			GlobalFree(pPerHandle);
			GlobalFree(pIoData);
			continue;
		}

		if (dwTrans == 0 && (pIoData->nOperationType == OP_READ || pIoData->nOperationType == OP_WRITE)) {
			closesocket(pPerHandle->s);
			GlobalFree(pPerHandle);
			GlobalFree(pIoData);
			
			std::cout << "close socket " << inet_ntoa(pPerHandle->addr.sin_addr)
				      << ":" << ntohs(pPerHandle->addr.sin_port) << std::endl;
			continue;
		}
		
		switch (pIoData->nOperationType) {
		case OP_READ:
			{
				// 取得数据
				pIoData->buf[dwTrans] = '\0';
				std::cout << "[" << inet_ntoa(pPerHandle->addr.sin_addr) << ":" 
					      << ntohs(pPerHandle->addr.sin_port) << "] " 
					      << pIoData->buf << std::endl;

				// 继续投递接收操作
				WSABUF buf;
				buf.buf = pIoData->buf;
				buf.len = BUFFER_SIZE;
				pIoData->nOperationType = OP_READ;

				DWORD dwRecv = 0;
				DWORD dwFlags = 0;
				WSARecv(pPerHandle->s, &buf, 1, &dwRecv, &dwFlags, &pIoData->ol, NULL);
			}
		case OP_WRITE:
			break;
		case OP_ACCEPT:
			break;
		default:
			break;
		}
	}
}
