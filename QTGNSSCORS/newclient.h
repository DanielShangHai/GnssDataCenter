#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QTcpSocket>

class NewClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit NewClient(QObject *parent = 0,int clientID=0);
private:
    int clientID;
signals:
    void ClientReadData(QString IP,int Port,QByteArray data);
    void ClientDisConnect(int clientID,QString IP,int Port);

private slots:
    void ReadData();
    void DisConnect();

public slots:

};
#endif // MYTCPCLIENT_H
