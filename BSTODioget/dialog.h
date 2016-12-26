#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore/QCoreApplication>
#include <QSettings>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
    void on_Determine_clicked();

    void on_Cancel_clicked();

private:
    Ui::Dialog *ui;
      void Init();
signals:
    void sendData(QString);   //用来传递数据的信号
};

#endif // DIALOG_H
