#include "RefStation.h"


CRefStation::CRefStation()
: m_ListenPort(0)
, m_ptrThreadListen(NULL)
, m_ptrThreadRecData(NULL)
, m_recDataLen(0)
, m_ListenThreadFlag(0)
{
}


CRefStation::~CRefStation()
{
}


bool CRefStation::Initialize()  //这里放初始化 监听端口以及其他的代码
{
	return false;
}


bool CRefStation::StartListen()
{

	if (m_ptrThreadListen==NULL)
	{
		m_ptrThreadListen = AfxBeginThread(CRefStation::RefStationListenThreadFun, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
		this->m_ListenThreadFlag = 1;
		m_ptrThreadListen->ResumeThread();
	}

	return true;
}


///这里做监听 参考站 accept 的工作
UINT CRefStation::RefStationListenThreadFun(LPVOID pParam)
{
	CRefStation *pRefStation = (CRefStation*)pParam;
	while (pRefStation->m_ListenThreadFlag)
	{
		;
		;
		if (pRefStation->m_ptrThreadRecData == NULL)
		{
			// 启动接收数据的线程
			;//m_ptrThreadRecData = AfxBeginThread(CRefStation::RefStationDataProcessThreadFun, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
		}
	}
	return 0L;
}


///这里做处理 参考站 接收数据并处理 发送给客户端
UINT CRefStation::RefStationDataProcessThreadFun(LPVOID pParam)
{
	CRefStation *pRefStation = (CRefStation*)pParam;
	while (pRefStation->m_DataProcessThreadFlag)
	{
		;
		;
		// 收到数据后
		ClientListDef::iterator it;
		pRefStation->m_mutexClientList.Lock();
		it = (pRefStation->m_clientSocketPtrList).begin();
		for (; it != pRefStation->m_clientSocketPtrList.end(); it++)
		{

			SOCKET client_socket = (*it)->m_ComuSocket;

			;//// senddata 给这个Socket   send(client_socket, databuff,datalen,0);
		}
		pRefStation->m_mutexClientList.Unlock();
		
	}
	return 0L;
}




bool CRefStation::AddClientForServe(GNSSCLIENT::CGnssClientptr prtclient)
{
	m_mutexClientList.Lock();
	m_clientSocketPtrList.push_back(prtclient);
	m_mutexClientList.Unlock();
	return true;
}


///这里做监听 客户 accept 的工作
UINT CRefStation::ClientListenThreadFun(LPVOID pParam)
{
	CRefStation *pRefStation = (CRefStation*)pParam;
	while (pRefStation->m_ClientListenThreadFlag)
	{
		;
		;//accept到之后

		GNSSCLIENT::CGnssClientptr newClient = new GNSSCLIENT::CGnssClient;
		pRefStation->AddClientForServe(newClient);
	}
	return 0L;
}
