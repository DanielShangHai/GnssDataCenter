#include "clientmanage.h"

ClientManage::ClientManage(QObject *parent) :
    QTcpServer(parent)
{
    ;
}
ClientManage::~ClientManage()
{

}

void ClientManage::SetSourceTable(DifferSourceTable* lpTable)
{
    m_lpSourceTable = lpTable;
}

void ClientManage::incomingConnection(qintptr handle)
{
     NewClient *client=new NewClient(this,handle);
     client->setSocketDescriptor(handle);
     connect(client,SIGNAL(ClientReadData(QString,int,QByteArray)),this,SLOT(ClientReadData(QString,int,QByteArray)));
     //connect(client,SIGNAL(ClientDisConnect(int,QString,int)),this,SLOT(DisConnect(int,QString,int)));

     CurrentClient=client;//放置当前Client
}
void ClientManage::ClientReadData(QString IP,int Port,QByteArray data)
{
    if (!data.isEmpty())
    {
        char dest[20] = { 0 };       //定义一个空数组
        strncpy_s(dest, data, 6);   //把一个数组的多少位赋值给另一个数组
        dest[5] = '\0';
      //  qDebug()  << "sendText: " << data;
       // qDebug()  << "Mdata: " << dest;
        char Nmsg1[] = "GET /";     //判断发送源节点的标识符
        char Nmsg2[] = "GET /SZRTCM2";    //判断发送数据的标识符
        char sendcaster1[] = "SOURCETABLE 200 OK\r\nSTR;BHRTCM32;BHRTCM32;RTCM 2.3;1(1),3(10),18(1),19(1);2;GPS;GPSNet;CHN;0.00;0.00;1;1;Trimble GPSNet;none;B;N;0;\r\nENDSOURCETABLE";
        //调用this->LinkClientAndBaseSource(m_lpSourceTable,CurrentClient,sourcetype);函数
         QString string = data;
         QStringList strlist=string.split("/");
         qDebug() <<strlist[1];
         QString string1=strlist[1];
         QString string2=string1.left(string1.length()-5);//Client中所包含的源节点
         qDebug() <<string2;
        if (strcmp(dest, Nmsg1) == 0&&string1.length()==5)          //判断字符串是否相等，安字节
        {
          CurrentClient->write(sendcaster1);
          qDebug() <<"huoquyuanliebiaochenggong";
        }
        else if (strcmp(dest, Nmsg1) == 0&&string1.length()>5)    //判断字符串是否相等，安字节
         {
            QString sourcetype=string2;
            this->LinkClientAndBaseSource(CurrentClient,sourcetype);
            qDebug()  << "sourcetype: " << sourcetype;
         }
    }
}
bool ClientManage::LinkClientAndBaseSource(NewClient *client,QString sourcetype)
{
   // qDebug() << "ADDclient success";
    if(m_lpSourceTable->m_SourceMap.contains("BHRTCM32"))
    {
          qDebug()<< "GetSourceBaseStation success";
    }
    ptrBaseStation lpBaseStation = m_lpSourceTable->GetSourceBaseStation(sourcetype);
    if(lpBaseStation == NULL)
    {
        qDebug() << "ADDclient defeat";
        return false;
    }
    lpBaseStation->AddClient(client);
    //qDebug() << "ADDclient success";
    return true;
}
