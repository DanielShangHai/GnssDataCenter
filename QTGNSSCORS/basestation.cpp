#include "basestation.h"

BaseStation::BaseStation() :
     // QTcpServer(parent),
      m_StationName(""),
      m_ListenPort(0),
      m_DiffSourceType(""),
      m_recType(RT_NETR9),
      m_inListening(false)
{
     ;
}
void BaseStation::SetListenPort(quint32 port)//设置监听端口
{
    m_ListenPort = port;
}
void BaseStation::SetStationName(QString &str)//设置基站名字
{
    m_StationName = str;
}
QString BaseStation::GetBaseStationName()//获得基站名字
{
    return m_StationName;
}
void BaseStation::SetDiffSourceType(QString type)//设置源节点名字
{
    //ASSERT((type<=ST_RTCM32)&&(type>=ST_UNDEFINED));
    m_DiffSourceType = type;
}

QString BaseStation::GetDiffSourceType()//获得源节点的名字
{
    return m_DiffSourceType;
}

void BaseStation::SetReceiverType(RECEIVER_TYPE rectype)//设置接收机类型
{
    //ASSERT((rectype<=RT_UB580)&&(rectype>=RT_UNDEFINED));
    m_recType = rectype;
}

bool BaseStation::StartListen()//基站监听函数
{
    bool ret;
    if(!m_inListening)
    {
      ret =  listen(QHostAddress::Any,m_ListenPort);
       // ret =m_TcpServer->listen(QHostAddress::Any,m_ListenPort);//接收数据端口函数
    }
    else
    {
        ret = true;
    } \
    return ret;
}
void BaseStation::incomingConnection(qintptr handle)
{
     NewClient *client=new NewClient(this,handle);
     client->setSocketDescriptor(handle);
     connect(client,SIGNAL(ClientReadData(QString,int,QByteArray)),this,SLOT(ClientReadData(QString,int,QByteArray)));
}
void BaseStation::ClientReadData(QString IP,int Port,QByteArray data)
{
    if (!data.isEmpty())
    {
        qDebug()  << "Mdata:" << data;
        this->SendDataAll(data);
    }
}
void BaseStation::SendDataAll(QByteArray data)
{
    for (int i=0;i<m_ID;i++)
    {
        m_clients[i]->write(data);
    }
}
bool BaseStation::AddClient(NewClient *lpClient)//基站添加Client函数
{
    m_ID++;
    m_clients.push_back(lpClient);
    qDebug() << "ADDclient success";
    return true;
}
bool BaseStation::DelClient()//删除Client函数
{
    return false;
}
