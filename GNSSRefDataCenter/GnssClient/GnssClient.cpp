#include "GnssClient.h"

namespace GNSSCLIENT
{

CGnssClient::CGnssClient()
: m_strDataSource(_T(""))
, m_UserName(_T(""))
, m_Password(_T(""))
, m_StaticDataUpload(0)
, m_StaticDataDownload(0)
{
}


CGnssClient::~CGnssClient()
{
}


int CGnssClient::Initialize(SOCKET comsock)
{
	return 0;
}


}