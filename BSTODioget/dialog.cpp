#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
       this->Init();
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::Init()
{
    ui->CgrPort->setText("5000");//设置初始差分端口为5000
    ui->DataPort->setText("6000");//设置初始数据端口为6000

    ui->StationID->setText("ABCD");//设置初始基站ID为ABCD
    ui->StationName->setText("ABCD");//设置初始基站名字为ABCD
}

void Dialog::on_Determine_clicked()
{
        emit sendData(ui->StationID->text());  //获取lineEdit的输入并且传递出去
        QString iniFilePath = ui->StationID->text();
        QSettings settings(iniFilePath,QSettings::IniFormat);

        settings.setValue("Group1/Path",ui->CgrPort->text());
        settings.setValue("Group1/FileName",ui->DataPort->text());
        settings.setValue("Group2/Count",ui->StationID->text());
        settings.setValue("Group2/Price",ui->StationName->text());
        this->close();
}

void Dialog::on_Cancel_clicked()
{

}
