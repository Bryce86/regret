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
	
	FileHandle�ǹ������ļ������
	ExistingCompletionPort���Ѿ����ڵ���ɶ˿ڡ����ΪNULL����Ϊ�½�һ��IOCP��
	CompletionKey�Ǵ��͸��������Ĳ�����
	NumberOfConcurrentThreads���ж��ٸ��߳��ڷ��������Ϣ���С�
							 ������ExistingCompletionPort��Ϊ0��ʱ��ϵͳ���Ըò�����
							 ���ò���Ϊ0��ʾ����ͬʱ�����Ŀ�ڴ������������̷߳��ʸ���Ϣ���С�
	*/
	
	
	// ���������̴߳�����ɶ˿ڶ�����¼�
	HANDLE hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (!hIocp) {
		std::cout << "CreateIoCOmpletionPort failed." << std::endl;
		goto end;
	}

	// ��ȡCPU�����������̳߳�
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	for (DWORD i = 0; i < sysInfo.dwNumberOfProcessors * 2; ++ i) {
		// ���������̣߳���������ɶ˿���
		HANDLE th = CreateThread(NULL, 0, WorkerThread, hIocp, 0, NULL);
		if (!th) {
			std::cout << "Create thread handle failed." << std::endl;
			goto end;
		}
		CloseHandle(th);
	}

	// �����׽��֣��󶨣�����
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

		// ���յ������ӣ�Ϊ�䴴���Ը�per_handle�ṹ��������������ɶ˿ڶ���
		PPER_HANDLE_DATA pPerHandle = (PPER_HANDLE_DATA) GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		if (!pPerHandle) {
			break;
		}
		pPerHandle->s = sockRemote;
		pPerHandle->addr = remoteAddr;
		CreateIoCompletionPort((HANDLE)pPerHandle->s, hIocp, (DWORD)pPerHandle, 0);

		// Ͷ��һ����������
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
			WSARecv ֻ����ϵͳ�ύһ���첽�����������������������ݵ���֮�󷵻أ����ҷ�����ɶ���֪ͨ�����̣߳�
			����첽�������󵽴���ɣ������ύ������Ϊ�˽�����һ�����ݰ���Ҳ����˵��ÿ�����󷵻�֮������ٴ��ύ��

			����������
			1. ����һ��ǰ̨ȥ�ȴ��Ӵ�һ������(WSARecv)Ȼ��������������
			2. ��������һֱ�������ϼ������ļ�Ȼ���ø���Ȼ������ȴ������ļ�(loop)
			3. ǰ̨�Ӵ�����֮��ѿͻ����Ϸŵ����ϼ�֮��Ͳ������ȥǰ̨�Ӵ�������
			4. ���ʱ������㲻����ǰ̨����ȥ�ȴ��Ӵ�����(WSARecv)����ô������ϼв������µ������ˣ�
			   ��ʱ����Ҫ�ٴ�ָ��ǰ̨ȥ�ȴ��Ӵ��µĿ���(�ٴ�WSARecv)��
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
				// ȡ������
				pIoData->buf[dwTrans] = '\0';
				std::cout << "[" << inet_ntoa(pPerHandle->addr.sin_addr) << ":" 
					      << ntohs(pPerHandle->addr.sin_port) << "] " 
					      << pIoData->buf << std::endl;

				// ����Ͷ�ݽ��ղ���
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
