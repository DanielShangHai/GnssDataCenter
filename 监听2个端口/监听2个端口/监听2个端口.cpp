// ����2���˿�.cpp : �������̨Ӧ�ó������ڵ㡣
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
void ErrorHandling(char *message);
#define BUF_SIZE 1024

typedef struct
{
	SOCKET hClntSock;  //�׽��־��
	char buf[BUF_SIZE];
	WSABUF wsaBuf;     //��������WSASocket���ݵĻ���
} PER_IO_DATA, *LPPER_IO_DATA;

LPPER_IO_DATA hbInfo;
unsigned int __stdcall listeningThread(void *param)
{
	SOCKET hLisnSock, hRecvSock;
	SOCKADDR_IN lisnAdr, recvAdr;
	LPWSAOVERLAPPED lpOvLp;
	DWORD recvBytes;
	/*LPPER_IO_DATA hbInfo;*/
	DWORD mode = 1, flagInfo = 0;
	int recvAdrSz;

	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	ioctlsocket(hLisnSock, FIONBIO, &mode);   // ���÷�����ģʽ

	memset(&lisnAdr, 0, sizeof(lisnAdr));       //��lisnAdr�е�ǰλ�ú����n���ֽ� �� ch �滻������lisnAdr
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
		SleepEx(100, TRUE);        // alertable�ȴ�״̬,SleepEx�������÷�
		hRecvSock = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
		if (hRecvSock == INVALID_SOCKET)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			else
				ErrorHandling("accept() error");
		}
		puts("Client connected.....");
		lpOvLp = (LPWSAOVERLAPPED)malloc(sizeof(WSAOVERLAPPED));  //�����ص�I/O����Ҫʹ�õĽṹ��������ڲ��ռ��ʼ��
		memset(lpOvLp, 0, sizeof(WSAOVERLAPPED));
		hbInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		hbInfo->hClntSock = (DWORD)hRecvSock;
		(hbInfo->wsaBuf).buf = hbInfo->buf;     //hbInfo->wsaBufΪ���յ�����
		(hbInfo->wsaBuf).len = BUF_SIZE;
		/*printf("%p\n", &(hbInfo->buf));*/

		lpOvLp->hEvent = (HANDLE)hbInfo;
		WSARecv(hRecvSock, &(hbInfo->wsaBuf),
			1, &recvBytes, &flagInfo, lpOvLp, NULL); //ע��

		//printf("%d\n", hbInfo->wsaBuf.buf);  

	}
	closesocket(hRecvSock);
	closesocket(hLisnSock);
	WSACleanup();
	getchar();
	return 0;
}
unsigned int __stdcall listeningThread1(void *param)
{

	SOCKET hLisnSock, hRecvSock;
	SOCKADDR_IN lisnAdr, recvAdr;
	LPWSAOVERLAPPED lpOvLp;
	/*LPPER_IO_DATA hbInfo;*/
	DWORD mode = 1, flagInfo = 0;
	DWORD recvBytes;
	int recvAdrSz;

	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	ioctlsocket(hLisnSock, FIONBIO, &mode);      // ���÷�����ģʽ

	memset(&lisnAdr, 0, sizeof(lisnAdr));       //��lisnAdr�е�ǰλ�ú����n���ֽ� �� ch �滻������lisnAdr
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
		SleepEx(100, TRUE);        // alertable�ȴ�״̬,SleepEx�������÷�
		hRecvSock = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
		if (hRecvSock == INVALID_SOCKET)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			else
				ErrorHandling("accept() error");
		}
		puts("Client connected.....");
		lpOvLp = (LPWSAOVERLAPPED)malloc(sizeof(WSAOVERLAPPED));  //�����ص�I/O����Ҫʹ�õĽṹ��������ڲ��ռ��ʼ��
		memset(lpOvLp, 0, sizeof(WSAOVERLAPPED));
		hbInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		hbInfo->hClntSock = (DWORD)hRecvSock;
		(hbInfo->wsaBuf).buf = hbInfo->buf;     //hbInfo->wsaBufΪ���յ�����
		(hbInfo->wsaBuf).len = BUF_SIZE;

		WSASend(hRecvSock, &(hbInfo->wsaBuf),
			1, &recvBytes, 0, lpOvLp, NULL); //ע��
	}
	closesocket(hRecvSock);
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
	_beginthreadex(NULL, 0, listeningThread, (void *)6000, 0, NULL);
	Sleep(INFINITE);
}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}