#include "newclient.h"
#include <QHostAddress>

NewClient::NewClient(QObject *parent,int clientID) :
    QTcpSocket(parent)
{
    this->clientID=clientID;
    connect(this,SIGNAL(readyRead()),this,SLOT(ReadData()));//挂接读取数据信号
    connect(this,SIGNAL(disconnected()),this,SLOT(DisConnect()));//关闭连接时，发送断开连接信号
}
void NewClient::ReadData()
{
    QByteArray data=this->readAll();
    emit ClientReadData(this->peerAddress().toString(),this->peerPort(),data);
}
void NewClient::DisConnect()
{
    //断开连接时，发送断开信号
    emit ClientDisConnect(this->clientID,this->peerAddress().toString(),this->peerPort());
}


