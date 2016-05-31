#ifndef __IOCP_H__
#define __IOCP_H__

#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "kernel32.lib")

#define BUFFER_SIZE 1024

#define PORT 7788

#define OP_READ 1
#define OP_WRITE 2
#define OP_ACCEPT 3

typedef struct _PER_HANDLE_DATA {
	SOCKET s; // 对应的套接字句柄
	sockaddr_in addr; // 对方的地址
}PER_HANDLE_DATA, *PPER_HANDLE_DATA;

typedef struct _PER_IO_DATA {
	OVERLAPPED ol; // 重叠结构
	WSABUF DataBuf; // 投递buffer
	char buf[BUFFER_SIZE]; // 实际数据缓冲区，赋值给DataBuf.buf
	int nOperationType; // 操作类型
}PER_IO_DATA, *PPER_IO_DATA;

#endif /* __IOCP_H__ */
