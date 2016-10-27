// ����2���˿�ת��.cpp : �������̨Ӧ�ó������ڵ㡣
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
typedef struct
{
	SOCKET hClntSock;  //�׽��־��
	char buf[BUF_SIZE];
	WSABUF wsaBuf;     //��������WSASocket���ݵĻ���
} PER_IO_DATA, *LPPER_IO_DATA;
LPPER_IO_DATA hbInfo, hbInfo1;
LPWSAOVERLAPPED lpOvLp, lpOvLp1;
SOCKET hRecvSock1;
unsigned int __stdcall listeningThread(void *param)
{
	SOCKET hLisnSock, hRecvSock;
	SOCKADDR_IN lisnAdr, recvAdr;
	LPWSAOVERLAPPED lpOvLp;
	/*LPPER_IO_DATA hbInfo;*/
	DWORD mode = 1, flagInfo = 0;
	int recvAdrSz;
	hLisnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	ioctlsocket(hLisnSock, FIONBIO, &mode);      // ���÷�����ģʽ

	memset(&lisnAdr, 0, sizeof(lisnAdr));      //��lisnAdr�е�ǰλ�ú����n���ֽ� �� ch �滻������lisnAdr
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
		SleepEx(100, TRUE);              // alertable�ȴ�״̬,SleepEx�������÷�
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
	puts("12");
	printf("%d\n", hbInfo->wsaBuf.buf);  
	//��ô��ȡ�ڶ����ͻ��˵��׽���
	/*LPPER_IO_DATA hbInfo1 = (LPPER_IO_DATA)(lpOverlapped->hEvent);   */
	SOCKET hSock = hRecvSock1;
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
		WSASend(hSock, bufInfo, 1, &recvBytes, 0, lpOverlapped, WriteCompRoutine);//ע��
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
		1, &recvBytes, &flagInfo, lpOverlapped, ReadCompRoutine);//ע��
}


unsigned int __stdcall listeningThread1(void *param)
{
	SOCKET hLisnSock;
	SOCKADDR_IN lisnAdr, recvAdr;
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
		hRecvSock1 = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
		if (hRecvSock1 == INVALID_SOCKET)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			else
				ErrorHandling("accept() error");
		}
		puts("Client connected.....");
		lpOvLp1 = (LPWSAOVERLAPPED)malloc(sizeof(WSAOVERLAPPED));     
		memset(lpOvLp1, 0, sizeof(WSAOVERLAPPED));
		hbInfo1 = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		hbInfo1->hClntSock = (DWORD)hRecvSock1;
		(hbInfo1->wsaBuf).buf = hbInfo1->buf;     //hbInfo->wsaBufΪ���յ�����
		(hbInfo1->wsaBuf).len = BUF_SIZE;
		lpOvLp1->hEvent = (HANDLE)hbInfo1;
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