#ifndef MFCORS1_H
#define MFCORS1_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
class MFCORS1 : public QMainWindow
{
    Q_OBJECT

public:
    MFCORS1(QWidget *parent = 0);
    ~MFCORS1();
    void createActions();                        	//创建动作
    void createMenus();                           	//创建菜单
    void createToolBars();                      	//创建工具栏

    private:
    QMenu *BstationM;           //基站管理
    QMenu *UserM;               //用户管理
    QMenu *FileM;              //文件管理
    QMenu *SubnetM;           //子网管理
    QMenu *SystemM;            //  系统管理
    QMenu *ToolM;             //工具
    QMenu *ABOUTM;            //关于
    QMenu *HELPM;             //帮助


      QAction *AddStation;                     	//添加基站动作
     QAction *DelStation;                       //删除基站动作

      QAction  *Sunit;                           //个人单位
      QAction  *Cunit;                          //集体单位


     protected slots:
        void StationPro();                //基站属性(添加基站、基站属性调用的函数)
        void DelStationPro();            //删除基站

};

#endif // MFCORS1_H
