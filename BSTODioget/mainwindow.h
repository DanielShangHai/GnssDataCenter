#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "dialog.h"
#include <QTime>
#include "mytcpserver.h"
#include "mytcpserver1.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    void createItemMenu();
    void contextMenuEvent(QContextMenuEvent *event);
private:
     QMenu *BaseStationM;
     QMenu *BaseStationS;

     QAction *BaseStationAdd;
     QAction *BaseStationDel;
     QAction *BaseStationStr;
     QAction *BaseStationMod;
     QTreeWidgetItem *BaseStationD;
     Dialog *dlg;
     QString data1;
private slots:

    //服务端槽函数
    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientConnect(int clientID,QString IP,int Port);
    void ClientDisConnect(int clientID,QString IP,int Port);

    void ClientConnect1(int clientID,QString IP,int Port);
    void ClientDisConnect1(int clientID,QString IP,int Port);

private slots:
    void receiveData(QString data);   //接收传递过来的数据的槽
private slots:
    void onMemberMenuTriggered(QAction *action);
     void onOPen(QAction *action);
    QTreeWidgetItem * AddTreeNode(QTreeWidgetItem *parent,QString name);
private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpClient;
    myTcpServer *tcpServer;
    myTcpServer1 *tcpServer1;
};

#endif // MAINWINDOW_H
