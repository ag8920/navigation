#include "tableform.h"
#include "ui_tableform.h"
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>
#include <QString>
#include <QDebug>

TableForm::TableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableForm),
    isConnectPort(false)
{
    ui->setupUi(this);
    PortSettingsDialog *settingPort = new PortSettingsDialog();
    gridButtons = new buttonGrid("Z","Y");

    QGridLayout *tab2Layout = new QGridLayout();
    tab2Layout->addWidget(gridButtons);
    ui->tab_2->setLayout(tab2Layout);
    connect(gridButtons, &buttonGrid::pressButton,this, &TableForm::pressMoveButton );

    connect(ui->ButtonConnect, &QPushButton::clicked,
            this,&TableForm::clickedConnectButton);
    connect(ui->ButtonUpdateInfo, &QPushButton::clicked,
            this, &TableForm::fillPortsInfo);
    connect(ui->baudRateBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(checkCustomBaudRatePolicy(int)));

    connect(ui->pushButtonUp, &QPushButton::clicked,
            this, &TableForm::clickedUpButton);
    connect(ui->pushButtonDown, &QPushButton::clicked,
            this, &TableForm::clickedDownButton);
    connect(ui->pushButtonLeft, &QPushButton::clicked,
            this, &TableForm::clickedLeftButton);
    connect(ui->pushButtonRight, &QPushButton::clicked,
            this, &TableForm::clickedRightButton);
    connect(ui->pushButtonHome, &QPushButton::clicked,
            this, &TableForm::clickedHomeButton);

    connect(ui->radioButton, &QRadioButton::toggled,
            this, &TableForm::setTypeMove);

    fillBaudRateParametres();
    fillPortsInfo();

    ui->ButtonConnect->setIcon(QIcon(":/icons/icons/disconnect.png"));
    ui->ButtonUpdateInfo->setIcon(QIcon(":/icons/Refresh.png"));

    ui->radioButton->setChecked(true);

    ui->comboBox->hide();

    ui->tabWidget->setCurrentIndex(0);

}

TableForm::~TableForm()
{
    delete ui;
}

void TableForm::fillBaudRateParametres()
{
    ui->baudRateBox->addItem(QStringLiteral("1200"), QSerialPort::Baud1200);
    ui->baudRateBox->addItem(QStringLiteral("2400"), QSerialPort::Baud2400);
    ui->baudRateBox->addItem(QStringLiteral("4800"), QSerialPort::Baud4800);
    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateBox->addItem(QStringLiteral("230400"),230400);
    ui->baudRateBox->addItem(QStringLiteral("921600"),921600);
    ui->baudRateBox->addItem(QStringLiteral("Custom"));
}

void TableForm::fillPortsInfo()
{
    ui->serialPortInfoBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
         QStringList list;
         list << info.portName();
         if(!info.isBusy()) ui->serialPortInfoBox->addItem(list.first(), list);
    }
}

void TableForm::checkCustomBaudRatePolicy(int idx)
{
    QIntValidator *intValidator=new QIntValidator(0,4000000,this);
    bool isCustomBaudRate = !ui->baudRateBox->itemData(idx).isValid();
    ui->baudRateBox->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        ui->baudRateBox->clearEditText();
        QLineEdit *edit = ui->baudRateBox->lineEdit();
        edit->setStyleSheet(" background-color: #232629;"
                            " padding: 1px;"
                            "border-style: solid;"
                            "border: 0px solid #76797C;"
                            "border-radius: 0px;"
                            "color: #eff0f1;");
        edit->setValidator(intValidator);
    }
}

void TableForm::clickedUpButton()
{
    if (ui->lineEditAngleY->text().isEmpty() || ui->lineEditSpeedY->text().isEmpty() )
        return;
    pressMoveButton(true,false,move,ui->lineEditSpeedY->text(),NULL,
                    ui->lineEditAngleY->text(),NULL);
}

void TableForm::clickedDownButton()
{
    if (ui->lineEditAngleY->text().isEmpty() || ui->lineEditSpeedY->text().isEmpty() )
        return;
    double AngleY=ui->lineEditAngleY->text().toDouble();
    AngleY=-AngleY;
    pressMoveButton(true,false,move,
                    ui->lineEditSpeedY->text(),
                    NULL,
                    QString::number(AngleY),NULL);
}

void TableForm::clickedLeftButton()
{
    if(ui->lineEditSpeedZ->text().isEmpty() || ui->lineEditAngleZ->text().isEmpty())
        return;
    pressMoveButton(false,true,move,NULL,
                    ui->lineEditSpeedZ->text(),
                    NULL,ui->lineEditAngleZ->text());
}

void TableForm::clickedRightButton()
{
    if(ui->lineEditAngleZ->text().isEmpty() ||ui->lineEditSpeedZ->text().isEmpty())
        return;
    double AngleZ=ui->lineEditAngleZ->text().toDouble();
    AngleZ=-AngleZ;
    pressMoveButton(false,true,move,NULL,
                    ui->lineEditSpeedZ->text(),
                    NULL,QString::number(AngleZ));
}

void TableForm::clickedHomeButton()
{
    pressMoveButton(true,true,true,"300","300",
                    "0","0");
}

void TableForm::setTypeMove()
{

    if(ui->radioButton->isChecked())
    {
        move=relativeMove;
    }
    else if(ui->radioButton_2->isChecked())
    {
        move=absoluteMove;
    }
}


void TableForm::clickedConnectButton()
{
    if(!isConnectPort){
        QString name=ui->serialPortInfoBox->currentText();
        int baud;
        if (ui->baudRateBox->currentIndex() == 9) {
            baud = ui->baudRateBox->currentText().toInt();
        } else {
            baud =/* static_cast<QSerialPort::BaudRate>*/(
                ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt());
        }
        emit ConnectPort(name,baud,
                    QSerialPort::Data8,
                    QSerialPort::NoParity,
                    QSerialPort::OneStop,
                    QSerialPort::NoFlowControl);
        qDebug()<<"TableForm::clickedConnectButton():: connected";
    }
    else{
        emit disconnectPort();
        qDebug()<<"TableForm::clickedConnectButton():: disconnected";
    }
}

void TableForm::ConnectedPort(bool arg1)
{
    isConnectPort=arg1;
    if(isConnectPort)
    {
         ui->ButtonConnect->setIcon(QIcon(":/icons/icons/connect.png"));
         ui->ButtonConnect->setText(tr("Отключить"));
         ui->ButtonUpdateInfo->setEnabled(false);
         ui->baudRateBox->setEnabled(false);
         ui->serialPortInfoBox->setEnabled(false);

         ui->pushButtonUp->setEnabled(true);
         ui->pushButtonDown->setEnabled(true);
         ui->pushButtonLeft->setEnabled(true);
         ui->pushButtonRight->setEnabled(true);

    }
    else
    {
        ui->ButtonConnect->setIcon(QIcon(":/icons/icons/disconnect.png"));
        ui->ButtonConnect->setText(tr("Подключить"));
        ui->ButtonUpdateInfo->setEnabled(true);
        ui->baudRateBox->setEnabled(true);
        ui->serialPortInfoBox->setEnabled(true);

        ui->pushButtonUp->setEnabled(false);
        ui->pushButtonDown->setEnabled(false);
        ui->pushButtonLeft->setEnabled(false);
        ui->pushButtonRight->setEnabled(false);
    }
}











