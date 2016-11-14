#pragma once
#include <vector>
#include <list>
#include <afxwin.h>

using namespace std;
namespace GNSSCLIENT
{

class CGnssClient
{
public:
	CGnssClient();
	~CGnssClient();
private:
	
	// Ô´Êý¾Ý
	CString m_strDataSource;
	CString m_UserName;
	CString m_Password;
	int m_StaticDataUpload;
	int m_StaticDataDownload;
public:
	SOCKET m_ComuSocket;
	int Initialize(SOCKET comsock);
};

typedef CGnssClient*  CGnssClientptr;

}