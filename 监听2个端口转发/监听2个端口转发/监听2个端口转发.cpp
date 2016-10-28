// 监听2个端口转发.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib")
using namespace std;
void CALLBACK ReadCompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK WriteCompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void ErrorHandling(char *message);
#define BUF_SIZE 1024

DWORD recvBytes;
int RemoteLen;
typedef struct tagPER_HANDLE_DATA
{
	SOCKET Socket;
	SOCKADDR_STORAGE ClientAddr;
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;
typedef struct
{
	SOCKET hClntSock;  //套接字句柄
	char buf[BUF_SIZE];
	WSABUF wsaBuf;     //用来接收WSASocket数据的缓冲
} PER_IO_DATA, *LPPER_IO_DATA;
LPPER_IO_DATA hbInfo, hbInfo1;
LPWSAOVERLAPPED lpOvLp, lpOvLp1;
SOCKET hRecvSock1;
PER_HANDLE_DATA *PerHandleData = NULL;
unsigned int __stdcall listeningThread(void *param)
{
	SOCKET hLisnSock, hRecvSock;
	SOCKADDR_IN lisnAdr, recvAdr;
	LPWSAOVERLAPPED lpOvLp;
	/*LPPER_IO_DATA hbInfo;*/
	DWORD mode = 1, flagInfo = 0;
	int recvAdrSz;
	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	ioctlsocket(hLisnSock, FIONBIO, &mode);      // 设置非组赛模式

	memset(&lisnAdr, 0, sizeof(lisnAdr));      //将lisnAdr中当前位置后面的n个字节 用 ch 替换并返回lisnAdr
	lisnAdr.sin_family = AF_INET;
	lisnAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	lisnAdr.sin_port = htons((int)param);

	if (bind(hLisnSock, (SOCKADDR*)&lisnAdr, sizeof(lisnAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	if (listen(hLisnSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");
	recvAdrSz = sizeof(recvAdr);
	while (1)
	{
		SleepEx(100, TRUE);              // alertable等待状态,SleepEx函数的用法
		hRecvSock = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
		if (hRecvSock == INVALID_SOCKET)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			else
				ErrorHandling("accept() error");
		}
		puts("Client connected.....");
		lpOvLp = (LPWSAOVERLAPPED)malloc(sizeof(WSAOVERLAPPED));  //申请重叠I/O中需要使用的结构体变量的内部空间初始化
		memset(lpOvLp, 0, sizeof(WSAOVERLAPPED));

		hbInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		hbInfo->hClntSock = (DWORD)hRecvSock;
		(hbInfo->wsaBuf).buf = hbInfo->buf;
		(hbInfo->wsaBuf).len = BUF_SIZE;

		lpOvLp->hEvent = (HANDLE)hbInfo;
		WSARecv(hRecvSock, &(hbInfo->wsaBuf),
			1, &recvBytes, &flagInfo, lpOvLp, ReadCompRoutine);
	}
	closesocket(hRecvSock);
	closesocket(hLisnSock);
	WSACleanup();
	getchar();
	return 0;
}
void CALLBACK ReadCompRoutine(
	DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	//怎么提取第二个客户端的套接字
	SOCKET hSock = PerHandleData->Socket;
	LPWSABUF bufInfo = &(hbInfo->wsaBuf);
	if (szRecvBytes == 0)
	{
		closesocket(hSock);
		free(lpOverlapped->hEvent); free(lpOverlapped);
		puts("Client disconnected.....");
	}
	else
	{
		bufInfo->len = szRecvBytes;
		WSASend(hSock, bufInfo, 1, &recvBytes, 0, lpOverlapped, WriteCompRoutine);//注意
	}
}


void CALLBACK WriteCompRoutine(
	DWORD dwError, DWORD szSendBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{

	printf("%d\n", hbInfo->wsaBuf.buf);
	LPPER_IO_DATA hbInfo = (LPPER_IO_DATA)(lpOverlapped->hEvent);
	SOCKET hSock = hbInfo->hClntSock;
	LPWSABUF bufInfo = &(hbInfo->wsaBuf);
	DWORD flagInfo = 0;
	WSARecv(hSock, bufInfo,
		1, &recvBytes, &flagInfo, lpOverlapped, ReadCompRoutine);//注意
}


unsigned int __stdcall listeningThread1(void *param)
{
	SOCKET hLisnSock;
	SOCKADDR_IN lisnAdr, recvAdr;
	DWORD mode = 1, flagInfo = 0;
	int recvAdrSz;

	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	ioctlsocket(hLisnSock, FIONBIO, &mode);   // 设置非组赛模式

	memset(&lisnAdr, 0, sizeof(lisnAdr));       //将lisnAdr中当前位置后面的n个字节 用 ch 替换并返回lisnAdr
	lisnAdr.sin_family = AF_INET;
	lisnAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	lisnAdr.sin_port = htons((int)param);

	if (bind(hLisnSock, (SOCKADDR*)&lisnAdr, sizeof(lisnAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	if (listen(hLisnSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");
	//recvAdrSz = sizeof(recvAdr);
	recvAdrSz = sizeof(recvAdr);
	while (1)
	{
		SleepEx(100, TRUE);        // alertable等待状态,SleepEx函数的用法
		//recvAdrSz = sizeof(recvAdr);
		hRecvSock1 = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
		if (hRecvSock1 == INVALID_SOCKET)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			else
				ErrorHandling("accept() error");
		}
		PerHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));//第一个参数为分配属性(方式)，第二个为分配的字节数
		//PerHandleData为创建的句柄
		if (PerHandleData == NULL)
		{
			closesocket(hRecvSock1);
			return 0;
		}
		puts("Client connected.....");
		PerHandleData->Socket = hRecvSock1;
		memcpy(&PerHandleData->ClientAddr, &recvAdr, recvAdrSz);
	}
	closesocket(hRecvSock1);
	closesocket(hLisnSock);
	WSACleanup();
	getchar();
	return 0;
}

void main()
{

	WSADATA	wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	_beginthreadex(NULL, 0, listeningThread, (void *)5000, 0, NULL);
	_beginthreadex(NULL, 0, listeningThread1, (void *)6000, 0, NULL);
	Sleep(INFINITE);
}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}