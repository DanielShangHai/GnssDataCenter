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


bool CRefStation::Initialize()  //����ų�ʼ�� �����˿��Լ������Ĵ���
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


///���������� �ο�վ accept �Ĺ���
UINT CRefStation::RefStationListenThreadFun(LPVOID pParam)
{
	CRefStation *pRefStation = (CRefStation*)pParam;
	while (pRefStation->m_ListenThreadFlag)
	{
		;
		;
		if (pRefStation->m_ptrThreadRecData == NULL)
		{
			// �����������ݵ��߳�
			;//m_ptrThreadRecData = AfxBeginThread(CRefStation::RefStationDataProcessThreadFun, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
		}
	}
	return 0L;
}


///���������� �ο�վ �������ݲ����� ���͸��ͻ���
UINT CRefStation::RefStationDataProcessThreadFun(LPVOID pParam)
{
	CRefStation *pRefStation = (CRefStation*)pParam;
	while (pRefStation->m_DataProcessThreadFlag)
	{
		;
		;
		// �յ����ݺ�
		ClientListDef::iterator it;
		pRefStation->m_mutexClientList.Lock();
		it = (pRefStation->m_clientSocketPtrList).begin();
		for (; it != pRefStation->m_clientSocketPtrList.end(); it++)
		{

			SOCKET client_socket = (*it)->m_ComuSocket;

			;//// senddata �����Socket   send(client_socket, databuff,datalen,0);
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


///���������� �ͻ� accept �Ĺ���
UINT CRefStation::ClientListenThreadFun(LPVOID pParam)
{
	CRefStation *pRefStation = (CRefStation*)pParam;
	while (pRefStation->m_ClientListenThreadFlag)
	{
		;
		;//accept��֮��

		GNSSCLIENT::CGnssClientptr newClient = new GNSSCLIENT::CGnssClient;
		pRefStation->AddClientForServe(newClient);
	}
	return 0L;
}
