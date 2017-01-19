#ifndef ADDBASESTATIONDIALOG_H
#define ADDBASESTATIONDIALOG_H

#include <QDialog>
#include <QtCore/QCoreApplication>
#include <QSettings>
#include "basestation.h"

namespace Ui {
class ADDBaseStationDialog;
}

class ADDBaseStationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ADDBaseStationDialog(QWidget *parent = 0);
    ~ADDBaseStationDialog();

    quint32 m_ListenPort;
    QString m_BaseStationName;
    QString m_sourcetype;

private slots:
    void on_Determine_clicked();

    void on_Cancel_clicked();

private:
    Ui::ADDBaseStationDialog *ui;
      void Init();
signals:
    void sendData(QString);   //用来传递数据的信号
};

#endif // ADDBASESTATIONDIALOG_H
