#include "mytcpserver1.h"

myTcpServer1::myTcpServer1(QObject *parent) :
    QTcpServer(parent)
{
    this->clientCount=0;
}

void myTcpServer1::incomingConnection(qintptr handle)
{

    myTcpClient *client=new myTcpClient(this,handle);
    client->setSocketDescriptor(handle);

     connect(client,SIGNAL(ClientReadData(int,QString,int,QByteArray)),this,SLOT(ClientReadData1(int,QString,int,QByteArray)));
    //connect(client,SIGNAL(ClientReadData(int,QString,int,QByteArray)),this,SIGNAL(ClientReadData(int,QString,int,QByteArray)));
    connect(client,SIGNAL(ClientDisConnect(int,QString,int)),this,SLOT(DisConnect(int,QString,int)));

    emit ClientConnect(handle, client->peerAddress().toString(),client->peerPort());
    //ClientList.append(client);//将新的连接添加到客户端列表
    ClientID.append(handle);//将新的连接的ID添加到客户端ID列表
    //clientCount++;

    //存储当前连接
    CurrentClient=client;
}
void myTcpServer1::ClientReadData1(int clientID,QString IP,int Port,QByteArray data)
{
    if (!data.isEmpty())
    {
        char dest[20] = { 0 };       //定义一个空数组
        strncpy_s(dest, data, 13);   //把一个数组的多少位赋值给另一个数组
        dest[12] = '\0';
        qDebug()  << "sendText: " << data;
        qDebug()  << "Mdata: " << dest;
        char Nmsg1[] = "GET / HTTP/1";     //判断发送源节点的标识符
        char Nmsg2[] = "GET /SZRTCM2";    //判断发送数据的标识符
        char sendcaster1[] = "SOURCETABLE 200 OK\r\nSTR;SZRTCM2.3;SZRTCM23;RTCM 2.3;1(1),3(10),18(1),19(1);2;GPS;GPSNet;CHN;0.00;0.00;1;1;Trimble GPSNet;none;B;N;0;\r\nENDSOURCETABLE";
        if (strcmp(dest, Nmsg1) == 0)          //判断字符串是否相等，安字节
        {
         CurrentClient->write(sendcaster1);
        }
        if (strcmp(dest, Nmsg2) == 0)    //判断字符串是否相等，安字节
          {
            qDebug()  << "data: " << dest;
            ClientList.append(CurrentClient);//将新的连接添加到客户端列表
            clientCount++;
            //sleep(30);
         }
    }

}
void myTcpServer1::DisConnect(int clientID,QString IP,int Port)
{
    for (int i=0;i<clientCount;i++)
    {
        if (ClientID[i]==clientID)
        {
            ClientList.removeAt(i);//从列表中移除该连接
            ClientID.removeAt(i);
            clientCount--;
            i--;//不然的话，永远只会移除第一个连接
            emit ClientDisConnect(clientID,IP,Port);
            break;
        }
    }
}

//指定客户端连接发消息
//void myTcpServer::SendData(int clientID, QByteArray data)
//{
  //  for (int i=0;i<clientCount;i++)
  //  {
  //      if (ClientID[i]==clientID)
    //    {
      //      ClientList[i]->write(data);
      //      break;
     //   }
   // }
//}

//对当前连接发送数据
//void myTcpServer::SendDataCurrent(QByteArray data)
//{
    //如果没有一个存在的连接，则不处理
  //  if (clientCount<1){return;}
  //  CurrentClient->write(data);
//}

//对所有连接发送数据
void myTcpServer1::SendDataAll(QByteArray data)
{
    for (int i=0;i<clientCount;i++)
    {
        ClientList[i]->write(data);
    }
}

void myTcpServer1::CloseAllClient()
{
    for (int i=0;i<clientCount;i++)
    {
        ClientList[i]->close();
        i--;//不然的话，永远只会断开第一个连接
    }
}
