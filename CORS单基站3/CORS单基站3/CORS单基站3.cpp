// CORS����վ3.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <iostream> 
#define  _CRT_SECURE_NO_WARNINGS

#pragma comment (lib, "Ws2_32.lib")
using namespace std;
void CALLBACK ReadCompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void CALLBACK WriteCompRoutine(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
void ErrorHandling(char *message);
#define BUF_SIZE 1024
#define MAX_CLNT 256
DWORD recvBytes;

typedef struct tagPER_HANDLE_DATA
{
	SOCKET Socket;
	SOCKADDR_STORAGE ClientAddr;
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;
typedef struct
{
	SOCKET hClntSock;  //�׽��־��
	char buf[BUF_SIZE];
	WSABUF wsaBuf;     //��������WSASocket���ݵĻ���
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
	SOCKET hSock = PerHandleData->Socket;
	//��һ���жϣ����hSock��Ϊ�գ�����У����Ϊ����ͣ����ȵ�hSock��Ϊ��Ϊֹ
	puts("Client connected.....");
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
	int strLen = 0;
	char msg[BUF_SIZE] = { 0 };
	string res, s;
	//char Nmsg2[] = "GET /SZRTCM2.3 HTTP/1.0\r\nUser-Agent: NTRIP GNSSInternetRadio/1.4.3\r\nAccept: */*\r\nConnection: close\r\nAuthorization: Basic Y2VzaDpjZXNo\r\n\r\n";
	char Nmsg2[] = "GET /SZRTCM2";
	char Nmsg1[] = "GET / HTTP/1";
	//char Nms[] = "GET / HTTP/1.0\r\nUser-Agent: NTRIP GNSSInternetRadio/1.4.3\r\nAccept: */*\r\nConnection: close\r\nAuthorization: Basic Og==\r\n\r\n";
	char sendcaster1[] = "SOURCETABLE 200 OK\r\nSTR;SZRTCM2.3;SZRTCM23;RTCM 2.3;1(1),3(10),18(1),19(1);2;GPS;GPSNet;CHN;0.00;0.00;1;1;Trimble GPSNet;none;B;N;0;\r\nENDSOURCETABLE";
	char sendcaster2[] = "ICY 200 OK";
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
	//recvAdrSz = sizeof(recvAdr);
	recvAdrSz = sizeof(recvAdr);
	while (1)
	{
		SleepEx(100, TRUE);        // alertable�ȴ�״̬,SleepEx�������÷�
		//recvAdrSz = sizeof(recvAdr);
		hRecvSock1 = accept(hLisnSock, (SOCKADDR*)&recvAdr, &recvAdrSz);
		if (hRecvSock1 == INVALID_SOCKET)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			else
				ErrorHandling("accept() error");
		}
		if ((strLen = recv(hRecvSock1, msg, sizeof(msg), 0)) != 0)
		{
			char dest[20] = { 0 };       //����һ��������
			strncpy_s(dest, msg, 13);   //��һ������Ķ���λ��ֵ����һ������
			dest[12] = '\0';            //û�л�����
			cout << "��������Ϊ��" << dest << endl;
			if (strcmp(dest, Nmsg1) == 0)          //�ж��ַ����Ƿ���ȣ����ֽ�
			{
				send(hRecvSock1, sendcaster1, sizeof(sendcaster1), 0);
				printf("Connected client\n");
			}
			if (strcmp(dest, Nmsg2) == 0)          //�ж��ַ����Ƿ���ȣ����ֽ�
			{
				send(hRecvSock1, sendcaster2, sizeof(sendcaster2), 0);
				//PerHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));//��һ������Ϊ��������(��ʽ)���ڶ���Ϊ������ֽ���
				if (PerHandleData == NULL)
				{
					closesocket(hRecvSock1);
					return 0;
				}
				puts("Client connected.....");
				PerHandleData->Socket = hRecvSock1;
				memcpy(&PerHandleData->ClientAddr, &recvAdr, recvAdrSz);
			}
		}
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
	PerHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
	_beginthreadex(NULL, 0, listeningThread, (void *)8200, 0, NULL);
	_beginthreadex(NULL, 0, listeningThread1, (void *)6000, 0, NULL);
	Sleep(INFINITE);
}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}