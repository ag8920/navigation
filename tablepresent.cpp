#include "tablepresent.h"

TablePreseneter::TablePreseneter(QObject *parent) : QObject(parent)
{
    mainForm=new TableForm;
    settingsForm=new PortSettingsDialog;
    modelTable=new controlTableGRBL;

    createConnect();
}

void TablePreseneter::createConnect()
{
    connect(mainForm, &TableForm::openSettings,settingsForm,
            &PortSettingsDialog::showWidget);
    connect(mainForm, &TableForm::disconnectPort,this,
            &TablePreseneter::closePort);
    connect(settingsForm, &PortSettingsDialog::isUpdateSettings,
            this, &TablePreseneter::openPort);    
}

void TablePreseneter::openPort()
{
    PortSettingsDialog::Settings p=settingsForm->settings();
    QString name=static_cast<QString>(p.name);
    int baudRate=static_cast<int>(p.baudRate);
    int dataBits=static_cast<int>(p.dataBits);
    int parity=static_cast<int>(p.parity);
    int stopBits=static_cast<int>(p.stopBits);
    int flowControl=static_cast<int>(p.flowControl);

    tableConnect=modelTable->ConnectPort(name,baudRate,dataBits,
                     parity,stopBits,flowControl);
    if(tableConnect)
    {

    }
}

void TablePreseneter::closePort()
{
    tableConnect=modelTable->DisconnectPort();
    if(!tableConnect)
    {

    }
}

void TablePreseneter::showWgt()
{
    mainForm->show();
}

