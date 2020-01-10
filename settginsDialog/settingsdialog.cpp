#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QSettings>
QString settingsDialog::getIPadresSender() const
{
    return IPadresSender;
}

QString settingsDialog::getIPadresReciever() const
{
    return IPadresreceiver;
}

quint16 settingsDialog::getPort() const
{
    return Port;
}

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);
    ui->lineEditIP->setInputMask("000.000.000.000");
    ui->lineEditIPreciever->setInputMask("000.000.000.000");
    ui->lineEditPort->setInputMask("0000");
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this,&settingsDialog::accept);
    readSettings();
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::accept()
{
//    emit outSettings(ui->lineEditIP->text(),ui->lineEditPort->text());
    IPadresSender = ui->lineEditIP->text();
    IPadresreceiver=ui->lineEditIPreciever->text();
    Port = ui->lineEditPort->text().toUInt();
    emit signalSettginsUpdate();
    writeSettings();
    this->hide();
}

void settingsDialog::readSettings()
{
    QSettings settings("settings.ini",QSettings::IniFormat);
    settings.beginGroup("udp_settings");
    ui->lineEditIP->setText(settings.value("IPsend","192.168.0.50").toString());
    ui->lineEditIPreciever->setText(settings.value("IPrec","192.168.0.150").toString());
    ui->lineEditPort->setText(settings.value("Port","1100").toString());
    settings.endGroup();
}

void settingsDialog::writeSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("udp_settings");
    settings.setValue("IPsend",IPadresSender);
    settings.setValue("IPrec",IPadresreceiver);
    settings.setValue("Port",Port);
    settings.endGroup();

}
