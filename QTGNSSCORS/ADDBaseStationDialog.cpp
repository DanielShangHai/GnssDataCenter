#include "ADDBaseStationDialog.h"
#include "ui_ADDBaseStationDialog.h"

ADDBaseStationDialog::ADDBaseStationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ADDBaseStationDialog)
{
    ui->setupUi(this);
       this->Init();
}

ADDBaseStationDialog::~ADDBaseStationDialog()
{
    delete ui;
}
void ADDBaseStationDialog::Init()
{
    ui->CgrPort->setText("5000");//设置初始差分端口为5000
    ui->DataPort->setText("6000");//设置初始数据端口为6000

    ui->StationID->setText("ABCD");//设置初始基站ID为ABCD
    ui->StationName->setText("ABCD");//设置初始基站名字为ABCD
}

void ADDBaseStationDialog::on_Determine_clicked()
{
        emit sendData(ui->StationID->text());  //获取lineEdit的输入并且传递出去
        QString iniFilePath = ui->StationID->text();
        QSettings settings(iniFilePath,QSettings::IniFormat);

        settings.setValue("Group1/Path",ui->CgrPort->text());
        settings.setValue("Group1/FileName",ui->DataPort->text());
        settings.setValue("Group2/Count",ui->StationID->text());
        settings.setValue("Group2/Price",ui->StationName->text());

        m_ListenPort = ui->CgrPort->text().toInt();
        m_BaseStationName = ui->StationName->text();
        m_sourcetype =ui->SourceEdit->text();
        accept();
        //this->close();
}
void ADDBaseStationDialog::on_Cancel_clicked()
{
      reject();
}
