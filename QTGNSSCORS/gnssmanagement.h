#ifndef GNSSMANAGEMENT_H
#define GNSSMANAGEMENT_H


#include <QMainWindow>
#include <QTreeWidget>
#include "basestation.h"
#include "Differsourcetable.h"
#include "ADDBaseStationDialog.h"
#include <QTime>
#include "clientmanage.h"
namespace Ui {
class GnssManagement;
}

class GnssManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit GnssManagement(QWidget *parent = 0);
    ~GnssManagement();
    void init();
    void createItemMenu();
    void contextMenuEvent(QContextMenuEvent *event);
    DifferSourceTable m_SourceTable;
    ClientManage m_ClientManger;
private:
     QMenu *BaseStationM;
     QMenu *BaseStationS;

     QAction *BaseStationAdd;
     QAction *BaseStationDel;
     QAction *BaseStationStr;
     QAction *BaseStationMod;
     QTreeWidgetItem *BaseStationD;
private slots:
    void onMemberMenuTriggered(QAction *action);
     void onOPen(QAction *action);
    QTreeWidgetItem * AddTreeNode(QTreeWidgetItem *parent,QString name);
private:
    Ui::GnssManagement *ui;
    ClientManage *clientmanage;
};

#endif // GNSSMANAGEMENT_H
