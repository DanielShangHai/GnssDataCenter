#ifndef MYTCPSERVER1_H
#define MYTCPSERVER1_H

#include <QTcpServer>
#include "mytcpclient.h"

class myTcpServer1 : public QTcpServer
{
    Q_OBJECT
public:
    explicit myTcpServer1(QObject *parent = 0);
    void SendData(int clientID, QByteArray data);
    void SendDataCurrent(QByteArray data);
    void SendDataAll(QByteArray data);

    int ClientCount()const{return clientCount;}
    void CloseAllClient();

private:
    QList<myTcpClient *> ClientList;
    QList<int> ClientID;
    myTcpClient *CurrentClient;

    int clientCount;

protected:
    void incomingConnection(qintptr handle);

signals:
    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientConnect(int clientID,QString IP,int Port);
    void ClientDisConnect(int clientID,QString IP,int Port);

private slots:
    void DisConnect(int clientID,QString IP,int Port);
    void ClientReadData1(int clientID,QString IP,int Port,QByteArray data);
public slots:

};
#endif // MYTCPSERVER1_H
