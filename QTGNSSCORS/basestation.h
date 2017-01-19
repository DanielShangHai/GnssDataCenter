#ifndef BASESTATION_H
#define BASESTATION_H

#include <QString>
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include "newclient.h"
#include <QList>

enum RECEIVER_TYPE
{
    RT_UNDEFINED = 0,
    RT_NETR9,
    RT_NETR5,
    RT_UB580
};
class BaseStation : QTcpServer
{
    Q_OBJECT
public:
    //explicit BaseStation(QObject *parent = 0);
    BaseStation();
    void SetListenPort(quint32 port);
    void SetStationName(QString &str);
    void SetDiffSourceType(QString type);
    void SetReceiverType(RECEIVER_TYPE rectype);
    void SendDataAll(QByteArray data);

    QString GetDiffSourceType();
    QString GetBaseStationName();
    bool AddClient(NewClient *lpClient);
    bool DelClient();
    bool StartListen();
private:
    QString m_StationName;
    int m_ID;
    quint32 m_ListenPort;
    QString m_DiffSourceType;
    RECEIVER_TYPE m_recType;
    bool m_inListening;
    NewClient*client;
    QList<NewClient *> m_clients;
protected:
    void incomingConnection(qintptr handle);
public slots:\
     void ClientReadData(QString IP,int Port,QByteArray data);
};
typedef BaseStation* ptrBaseStation;

#endif // BASESTATION_H
