// BCstation.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <winsock2.h> 
#include <string>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <process.h>
using namespace std;
void ErrorHandling(char * msg);
unsigned WINAPI RecvMsg(void * arg);


class  Bstation
{
public:
	Bstation(int it, string be) :iport(it), Bname(be)
	{
		it = 4000;
		port = iport = it;
		Bname = be;
	}
	void setBstation();                  // ���û�վ����
	void acceptBstation();              //��վ��������
	void inforwardBstation();          //��վ�ڲ�ת������ֶ˿ڣ�
	void showBstation();              //��վ������ʾ��ʵʱͼ��
	void skyshowBstation();          //��վ������ʾ���ǿ�ͼ��
	void saveBstation();            //��վ���ݱ���
	void RmanagementBstation();    //��վԶ�̹���
private:
	SOCKET hServSock, hClntSock;//���÷���˺Ϳͻ��˵��׽���
	int EWorkMode;
	int ErrorCode;
	HANDLE hSndThread, hRcvThread;//������������̺߳ͷ��������߳�
	const char * IP;//����IP
	int iport;//���ת�Ӷ˿�
	int port;//���ݽ���˿�
	string Bname;//��վ����
	SOCKADDR_IN servAdr, clntAdr;
};
void Bstation::acceptBstation()//ֻ��ΪServer�ı��
{
	WSADATA wsaData;
	int clntAdrSz;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));

	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(IP);
	servAdr.sin_port = htons(port);

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	while (1)
	{
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		hRcvThread =
			(HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hClntSock, 0, NULL);
		WaitForSingleObject(hRcvThread, INFINITE);
	}
	closesocket(hServSock);
	WSACleanup();
}
unsigned WINAPI RecvMsg(void * arg)   
{
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

void ErrorHandling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}