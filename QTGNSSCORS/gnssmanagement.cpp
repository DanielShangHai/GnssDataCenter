#include "gnssmanagement.h"
#include "ui_gnssmanagement.h"
#include <QMessageBox>
#include <QDebug>
GnssManagement::GnssManagement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GnssManagement)
{
    ui->setupUi(this);
    this->init();
    createItemMenu();
}
GnssManagement::~GnssManagement()
{
    delete ui;
}
void GnssManagement::init()
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
    clientmanage=new ClientManage(this);
    clientmanage->listen(QHostAddress::Any,6000);//接收数据端口函数
    clientmanage->SetSourceTable(&m_SourceTable);
}
void GnssManagement::createItemMenu()
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
void GnssManagement::onOPen(QAction *action)
{
    if (action == BaseStationStr)
    {       //启动基站
            QTreeWidgetItem*item =ui->Tree->currentItem();//获得当前节点
            QString BaseStationName=item->text(0);//获取节点的文本内容
            ptrBaseStation lpBaseStation = m_SourceTable.FindBaseStationByName(BaseStationName);
            if(lpBaseStation!=NULL)
            {
                if(lpBaseStation->StartListen())
                {
                    ui->txtDataServer->append("启动成功");
                }
                else
                {
                    QMessageBox::information(NULL, "Title", "监听端口失败，端口可能已经被占用", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                }
            }
    }
}
void GnssManagement::contextMenuEvent(QContextMenuEvent *event)
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

QTreeWidgetItem *GnssManagement::AddTreeNode(QTreeWidgetItem *parent,QString name)
{
    QTreeWidgetItem * item=new QTreeWidgetItem(QStringList()<<name);
    parent->addChild(item);
    return item;
}
void GnssManagement::onMemberMenuTriggered(QAction *action)
{
    if (action == BaseStationDel)
    {//删除基站

    }
    else if(action == BaseStationAdd)
    {//增加基站
        QTreeWidgetItem * item= ui->Tree->currentItem();
        if(item!=Q_NULLPTR)
        {
            ADDBaseStationDialog dlg;
            if(dlg.exec()==QDialog::Accepted)
            {
                QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                BaseStation *lpBaseStation  = new BaseStation;
                lpBaseStation->SetDiffSourceType(dlg.m_sourcetype);
                lpBaseStation->SetListenPort(dlg.m_ListenPort);
                lpBaseStation->SetStationName(dlg.m_BaseStationName);
                bool addSourceRet = m_SourceTable.AddDifferSource(lpBaseStation->GetDiffSourceType(),lpBaseStation);
                if(addSourceRet)
                {
                    AddTreeNode(item,dlg.m_BaseStationName);//增加基站的按钮
                }
                else
                {
                    QMessageBox::information(NULL, "Title", "添加基站失败，源类型重复", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                }
            }
        }
    }
    else if(action == BaseStationMod)
    {//修改基站
    }
}
