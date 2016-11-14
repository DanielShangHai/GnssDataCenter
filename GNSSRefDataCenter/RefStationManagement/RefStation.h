#pragma once
#include <afxwin.h>
#include <vector>
#include <list>
#include "GnssClient\GnssClient.h"
#include "afxmt.h"  //ʹ�� ����������Ҫ��ͷ�ļ�

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

	// �����������������Ժ���Ҫ,Ŀǰ�������տͻ��˵�����
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
	static UINT RefStationListenThreadFun(LPVOID pParam);  //��̬�����������˿ڡ������ն����ӵ��̺߳���  ���������ο�վ�Ľ���
	static UINT RefStationDataProcessThreadFun(LPVOID pParam);  //���������ο�վ���� ���̺߳���

	static UINT ClientListenThreadFun(LPVOID pParam);  //��̬�����������˿ڡ������ն����ӵ��̺߳���  ���������ͻ��˵Ľ���
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

