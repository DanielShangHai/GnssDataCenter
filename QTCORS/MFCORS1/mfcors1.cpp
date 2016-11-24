#include "mfcors1.h"

MFCORS1::MFCORS1(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle(tr("GNSSCORS"));
    //showWidget =new ShowWidget(this);
    //setCentralWidget(showWidget);
    createMenus();
}
void MFCORS1::createMenus()       //主菜单设计函数
{
    //基站管理菜单base station m
    BstationM =menuBar()->addMenu(tr("基站管理"));
    //BstationM->addAction(AddStation);
    //BstationM->addAction(DelStation);

    //用户管理菜单User management
    UserM =menuBar()->addMenu(tr("用户管理"));
    UserM->addAction(Sunit);    //个人单位
    UserM->addAction(Cunit);   //集体单位

    //文件菜单File management
    FileM =menuBar()->addMenu(tr("文件管理"));

    //子网菜单subnet
    SubnetM =menuBar()->addMenu(tr("子网管理"));


    //系统管理system m
    SystemM =menuBar()->addMenu(tr("系统管理"));


    //工具tool M
    ToolM =menuBar()->addMenu(tr("工具"));

    //关于  ABOUT
    ABOUTM =menuBar()->addMenu(tr("关于"));

    //帮助
    HELPM =menuBar()->addMenu(tr("帮助"));



}
void MFCORS1 ::createActions()    //创建动作函数
{
    //添加基站动作
    AddStation =new QAction(tr("添加基站"),this);
    connect(AddStation,SIGNAL(triggered()),this,SLOT(StationPro()));

    //删除基站动作
    DelStation=new QAction((tr("删除基站"),this));
    connect(DelStation,SIGNAL(triggered()),this,SLOT(DelStationPro()));

    //添加个人用户
   Sunit=new QAction(tr("个人用户"),this);

   //集体用户
   Cunit =new QAction(tr("集体用户"),this);
}
void MFCORS1::StationPro()  //添加基站，修改基站函数
{

}

void MFCORS1::DelStationPro()  //删除基站函数
{

}
MFCORS1::~MFCORS1()
{

}
