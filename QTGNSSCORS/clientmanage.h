#ifndef CLIENTMANAGE_H
#define CLIENTMANAGE_H

#include <QTcpServer>
#include <QTcpSocket>
#include "newclient.h"
#include "Differsourcetable.h"
class ClientManage : public QTcpServer
{
    Q_OBJECT
public:
    explicit ClientManage(QObject *parent = 0);
    ~ClientManage();
    NewClient *CurrentClient;
    DifferSourceTable* m_lpSourceTable;
    bool LinkClientAndBaseSource(NewClient *client,QString sourcetype);
    void SetSourceTable(DifferSourceTable* lpTable);
protected:
    void incomingConnection(qintptr handle);
private slots:
    //void DisConnect(int clientID,QString IP,int Port);
    void ClientReadData(QString IP,int Port,QByteArray data);
};

#endif // CLIENTMANAGE_H
