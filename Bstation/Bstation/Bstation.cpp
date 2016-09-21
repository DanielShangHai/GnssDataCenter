// Bstation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <winsock2.h>  
#include <string>  
using namespace std;
void ErrorHandling(char * msg);


class  Bstation
{
public:
	void setBstation();                  // 设置基站属性
	void acceptBstation();              //基站接收数据
	void inforwardBstation();          //基站内部转发（查分端口）
	void showBstation();              //基站数据显示（实时图表）
	void skyshowBstation();          //基站数据显示（星空图）
	void saveBstation();            //基站数据保存
	void RmanagementBstation();    //基站远程管理
private:
	SOCKET ServSock, hClntSock;//设置服务端和客户端的套接字
	int EWorkMode;
	int ErrorCode;
	SOCKADDR_IN servAdr;       
	HANDLE hSndThread, hRcvThread;//定义接收数据线程和发送数据线程
	const char * IP;//设置IP
	int iport;//差分转接端口
	int port;//数据接入端口
	string Bname;//基站名字

};
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