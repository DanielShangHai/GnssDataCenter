#include <QCoreApplication>
#include <QThread>
#include <stdio.h>
#include <QTNetwork/QTcpServer>
#include <QTNetwork/QTcpSocket>
#include <QDebug>
#include "mytcpserver.h"
#include "mytcpclient.h"

class  Listen1 : public QThread// 构造函数
{
public:
    Listen1(QObject *parent=0);
    QTcpServer *server;
    void run();
    void startListen();
private:
    QTcpSocket *tcpClient;
    myTcpServer *tcpServer;
private slots:
     void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
};

Listen1::Listen1(QObject *parent)
    :QThread(parent)
{
   tcpServer=new myTcpServer(this);
}

void Listen1::startListen()//启动服务器
{
    tcpServer->listen(QHostAddress::Any,6000);//listen函数
    connect(tcpServer,SIGNAL(ClientReadData(int,QString,int,QByteArray)),
            this,SLOT(ClientReadData(int,QString,int,QByteArray)));
}

void Listen1::run()//启动服务器
{

}

void Listen1::ClientReadData(int clientID,QString IP,int Port,QByteArray data)
{
    if (!data.isEmpty())
    {
           //如果数据不为空，则发送数据到另一个服务器
   qDebug() << "senduser " << clientID << "sendIP " << IP<<"sendPort " <<Port<< "sendText: " <<data;
    }
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Listen1 lis;//创建对象
    lis.startListen();
    lis.start();//启动线程
    return a.exec();
}
