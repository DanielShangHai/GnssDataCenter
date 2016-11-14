#pragma once
#include <afxwin.h>
#include <vector>
#include <list>
#include "GnssClient\GnssClient.h"
#include "afxmt.h"  //使用 互斥量所需要的头文件

using namespace std;


class CRefStation
{
public:
	CRefStation();
	~CRefStation();
private:
	SOCKET m_RefListenSocket;
	SOCKADDR_IN m_lisnAdr;
	UINT m_ListenPort;

	// 这里三个变量可能以后不需要,目前用来接收客户端的连接
	SOCKET m_ClientListenSocket;
	SOCKADDR_IN m_lisnAdrClient;
	UINT m_ListenPortClient;
	
	CWinThread* m_ptrThreadListen;
	CWinThread* m_ptrThreadRecData;
	unsigned char m_recDataBuff[256];
	int m_recDataLen;
	typedef list<GNSSCLIENT::CGnssClientptr> ClientListDef;
	ClientListDef m_clientSocketPtrList;
	CMutex m_mutexClientList;
	static UINT RefStationListenThreadFun(LPVOID pParam);  //静态函数，监听端口、处理终端连接的线程函数  用来监听参考站的接入
	static UINT RefStationDataProcessThreadFun(LPVOID pParam);  //用来监听参考站数据 的线程函数

	static UINT ClientListenThreadFun(LPVOID pParam);  //静态函数，监听端口、处理终端连接的线程函数  用来监听客户端的接入
public:
	bool Initialize();
	bool StartListen();
private:
	int m_ListenThreadFlag;
	int m_DataProcessThreadFlag;
	int m_ClientListenThreadFlag;

public:
	bool AddClientForServe(GNSSCLIENT::CGnssClientptr prtclient);
};

