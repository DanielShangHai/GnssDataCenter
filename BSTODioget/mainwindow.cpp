#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init();
    createItemMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init()
{
    QIcon icon;
    icon.addPixmap(QPixmap(":/image/openStatus.png"), QIcon::Normal, QIcon::On);//节点打开状态
    icon.addPixmap(QPixmap(":/image/closeStatus.png"), QIcon::Normal, QIcon::Off);//节点关闭状态

    ui->Tree->setColumnCount(1);
    QStringList headers;
    headers << QObject::tr("导航");
    ui->Tree->setHeaderLabels(headers);

    QStringList BaseStation;
    BaseStation << QObject::tr("基站管理");
    BaseStationD = new QTreeWidgetItem(ui->Tree, BaseStation);
    BaseStationD->setIcon(0,icon);

    QStringList subnet;
    subnet << QObject::tr("子网管理");
    QTreeWidgetItem *subnetD = new QTreeWidgetItem(ui->Tree, subnet);
    subnetD->setIcon(0,icon);

    QStringList Tuser;
    Tuser << QObject::tr("用户管路");
    QTreeWidgetItem * TuserD = new QTreeWidgetItem(ui->Tree,  Tuser);
    TuserD ->setIcon(0,icon);
    dlg = new Dialog;
    connect(dlg, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));


    tcpServer=new myTcpServer(this);
    tcpServer1=new myTcpServer1(this);
    connect(tcpServer,SIGNAL(ClientConnect(int,QString,int)),
            this,SLOT(ClientConnect(int,QString,int)));//连接客户端连接的信号

    connect(tcpServer,SIGNAL(ClientDisConnect(int,QString,int)),
            this,SLOT(ClientDisConnect(int,QString,int)));//连接客户端移除的信号

    connect(tcpServer,SIGNAL(ClientReadData(int,QString,int,QByteArray)),
            this,SLOT(ClientReadData(int,QString,int,QByteArray)));//连接接信号的消息

    connect(tcpServer1,SIGNAL(ClientConnect(int,QString,int)),
           this,SLOT(ClientConnect1(int,QString,int)));//连接客户端连接的信号

   connect(tcpServer1,SIGNAL(ClientDisConnect(int,QString,int)),
           this,SLOT(ClientDisConnect1(int,QString,int)));//连接客户端移除的信号

}
void MainWindow::receiveData(QString data)
{
    QTreeWidgetItem * item= ui->Tree->currentItem();
    data1=data;
    qDebug() << "clientIp: " << data1;
    AddTreeNode(item,data1);//增加基站的按钮
}
void MainWindow::createItemMenu()
{
      BaseStationM= new QMenu(this);
      BaseStationS= new QMenu(this);
      connect(BaseStationM,SIGNAL(triggered(QAction *)),
              this,SLOT(onMemberMenuTriggered(QAction *)));
      connect(BaseStationS,SIGNAL(triggered(QAction *)),
              this,SLOT(onOPen(QAction *)));
      BaseStationAdd = new QAction(tr("增加基站"),this);
      BaseStationDel = new QAction(tr("删除基站"),this);
      BaseStationMod = new QAction(tr("修改基站"),this);


      BaseStationStr = new QAction(tr("启动基站"),this);
}
void MainWindow::onOPen(QAction *action)
{
    if (action == BaseStationStr)
    {       //启动基站
            QTreeWidgetItem*item =ui->Tree->currentItem();//获得当前节点
            QString fileName=item->text(0);//获取节点的文本内容
            qDebug() << "节点: " << fileName;
            QString iniFilePath =  fileName;
            QSettings settings(iniFilePath,QSettings::IniFormat);
            int CPort = settings.value("Group1/Path").toInt();
            int DPort = settings.value("Group1/FileName").toInt();
            qDebug() << "clientIp: " << CPort;
            qDebug() << "clientIp: " << DPort;
            tcpServer->listen(QHostAddress::Any,CPort);//接收数据端口函数
            tcpServer1->listen(QHostAddress::Any,DPort);//接收数据端口函数
            ui->txtDataServer->append("启动成功");
    }

}
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem*item =ui->Tree->currentItem();//获得当前节点
    //QTreeWidgetItem* child=item->child(1);//获得当前节点的父节点
     if( item==BaseStationD)//判断选中的节点是什么
    {
        if (BaseStationM->isEmpty())
        {
            //添加基站
            BaseStationM->addAction(BaseStationAdd);
            //删除基站
            BaseStationM->addAction(BaseStationDel);
            //启动基站
            //BaseStationM->addAction(BaseStationStr);
        }
        BaseStationM->exec(QCursor::pos());
    }
      if(ui->Tree->currentItem()->parent()==BaseStationD&&ui->Tree->currentItem()->childCount()==0)//判断选中的节点是什么
      {
          if (BaseStationS->isEmpty())
          {
              //启动基站
              BaseStationS->addAction(BaseStationStr);
          }
           BaseStationS->exec(QCursor::pos());
      }
    //event->accept();
}

QTreeWidgetItem * MainWindow::AddTreeNode(QTreeWidgetItem *parent,QString name)
{
    QTreeWidgetItem * item=new QTreeWidgetItem(QStringList()<<name);
    parent->addChild(item);
    return item;
}
void MainWindow::onMemberMenuTriggered(QAction *action)
{
    if (action == BaseStationDel)
    {//删除基站

    }
    else if(action == BaseStationAdd)
    {//增加基站
        QTreeWidgetItem * item= ui->Tree->currentItem();
        if(item!=Q_NULLPTR)
        {
            dlg->show();
        }
    }
    else if(action == BaseStationMod)
    {//修改基站

    }
}
void MainWindow::ClientReadData(int clientID,QString IP,int Port,QByteArray data)
{
    if (!data.isEmpty())
    {
            ui->txtDataServer->append(tr("接收数据:%1 来自:[clientID:%2 IP:%3 Port:%4]")
                                      .arg(QString(data)).arg(clientID).arg(IP).arg(Port));
    }
}
void MainWindow::ClientConnect(int clientID,QString IP,int Port)
{
    ui->txtDataServer->append(tr("客户端[clientID:%1 IP:%2 Port:%3]上线时间:%4")
                              .arg(clientID).arg(IP).arg(Port).arg(QTime::currentTime().toString("hh:mm:ss")));
}
void MainWindow::ClientDisConnect(int clientID,QString IP,int Port)
{
    ui->txtDataServer->append(tr("客户端[clientID:%1 IP:%2 Port:%3]下线时间:%4")
                              .arg(clientID).arg(IP).arg(Port).arg(QTime::currentTime().toString("hh:mm:ss")));
}

void MainWindow::ClientConnect1(int clientID,QString IP,int Port)
{
    ui->txtDataServer->append(tr("客户端[clientID:%1 IP:%2 Port:%3]上线时间:%4")
                              .arg(clientID).arg(IP).arg(Port).arg(QTime::currentTime().toString("hh:mm:ss")));

}
void MainWindow::ClientDisConnect1(int clientID,QString IP,int Port)
{
    ui->txtDataServer->append(tr("客户端[clientID:%1 IP:%2 Port:%3]下线时间:%4")
                              .arg(clientID).arg(IP).arg(Port).arg(QTime::currentTime().toString("hh:mm:ss")));
}


