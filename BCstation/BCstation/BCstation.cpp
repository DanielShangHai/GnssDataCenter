// BCstation.cpp : 定义控制台应用程序的入口点。
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
	void setBstation();                  // 设置基站属性
	void acceptBstation();              //基站接收数据
	void inforwardBstation();          //基站内部转发（查分端口）
	void showBstation();              //基站数据显示（实时图表）
	void skyshowBstation();          //基站数据显示（星空图）
	void saveBstation();            //基站数据保存
	void RmanagementBstation();    //基站远程管理
private:
	SOCKET hServSock, hClntSock;//设置服务端和客户端的套接字
	int EWorkMode;
	int ErrorCode;
	HANDLE hSndThread, hRcvThread;//定义接收数据线程和发送数据线程
	const char * IP;//设置IP
	int iport;//差分转接端口
	int port;//数据接入端口
	string Bname;//基站名字
	SOCKADDR_IN servAdr, clntAdr;
};
void Bstation::acceptBstation()//只作为Server的编程
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