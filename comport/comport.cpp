//------------------------------------------------------------------------------
//     Данный модуль создает класс для управления
//     COM портом
//     Автор: Щербаков Александр
//     дата создания: 13.09.2018
//
//------------------------------------------------------------------------------
#include "comport.h"

#include <qdebug.h>
#include <QMessageBox>

comPort::comPort(QObject *parent) :
    QObject(parent)
{
    isConnectPort=false;
}
//-----------------------------------------------------------
// Назначение: конструктор класса
//-----------------------------------------------------------
comPort::~comPort()
{
    qDebug("comPort::~comPort()");
    DisconnectPort();
    emit finishedPort();//сигнал о завершении работы
}


void comPort::processPort() //выполняется при старте класса
{
    qDebug("comPort::processPort()");
    qDebug()<<"comPort threadID : "<<QThread::currentThreadId();
    qDebug()<<"comPort thread : "<<QThread::currentThread();
    connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)),
            this,SLOT(handleError(QSerialPort::SerialPortError)));
    connect(&thisPort,SIGNAL(readyRead()),
            this,SLOT(ReadInPort())); //подключаем чтение с порта по сигналу readyread()
}
//-----------------------------------------------------------
// Назначение: подключить порт
//-----------------------------------------------------------
void comPort::ConnectPort(QString name, int baudrate, int DataBits,
                          int Parity, int StopBits, int FlowControl)
{
    qDebug("comPort::ConnectPort()");
    if(thisPort.isOpen()){
        isNotConnectedPort(tr("%1 уже открыт").arg(thisPort.portName()));
        return;
    }

    SettingsPort.name = name;
    SettingsPort.baudRate = baudrate;
    SettingsPort.dataBits = static_cast<QSerialPort::DataBits> (DataBits);
    SettingsPort.parity = static_cast<QSerialPort::Parity> (Parity);
    SettingsPort.stopBits = static_cast<QSerialPort::StopBits> (StopBits);
    SettingsPort.flowControl = static_cast<QSerialPort::FlowControl> (FlowControl);

    thisPort.setPortName(SettingsPort.name);

    if(thisPort.open(QIODevice::ReadWrite))
    {
        if(thisPort.setBaudRate(SettingsPort.baudRate)
                && thisPort.setDataBits(SettingsPort.dataBits)
                && thisPort.setParity(SettingsPort.parity)
                && thisPort.setStopBits(SettingsPort.stopBits)
                && thisPort.setFlowControl(SettingsPort.flowControl))
        {
            if(thisPort.isOpen())
            {
                emit isConnectedPort(tr("Открыт порт: %1, %2, %3, %4, %5, %6")
                                .arg(name).arg(baudrate)
                                .arg(DataBits).arg(Parity)
                                .arg(StopBits).arg(FlowControl));
                emit boolConnectedPort(true);
                isConnectPort=true;
            }
            else
            {
                thisPort.close();
                error_(thisPort.errorString().toLocal8Bit());
                emit isNotConnectedPort(tr("Невозможно открыть порт %1").arg(name));
                isConnectPort=false;
                emit boolConnectedPort(false);
            }
        }
    }
    else
    {
        thisPort.close();
        error_(thisPort.errorString().toLocal8Bit());
        emit isNotConnectedPort(tr("Ошибка открытия порта"));
        emit boolConnectedPort(false);
        isConnectPort=false;
    }
}
//-----------------------------------------------------------
// Назначение: отключить порт
//-----------------------------------------------------------
bool comPort::DisconnectPort()
{
    qDebug("comPort::DisconnectedPort()");
    if(thisPort.isOpen())
    {
        thisPort.close();
        isNotConnectedPort(tr("%1 закрыт").arg(thisPort.portName()));
        emit boolConnectedPort(false);
        isConnectPort=false;
        return true;
    }
    else return false;

}
//-----------------------------------------------------------
// Назначение: проверка ошибок
//-----------------------------------------------------------
void comPort::handleError(QSerialPort::SerialPortError error)
{
    if((thisPort.isOpen())
            && (error == QSerialPort::ResourceError))
    {
        error_(thisPort.errorString().toLocal8Bit());
        DisconnectPort();
    }
}

bool comPort::getIsConnectPort() const
{
    return isConnectPort;
}

//-----------------------------------------------------------
// Назначение: отправка данных в COM порт
//-----------------------------------------------------------
bool comPort::WriteToPort(const QByteArray &data)
{
    qDebug()<<"comPort thread : "<<QThread::currentThread();
    if(thisPort.isOpen()){
        thisPort.write(data);
        return true;
    }
    return false;
}
//-----------------------------------------------------------
// Назначение: чтение данных из COM порта
//-----------------------------------------------------------
void comPort::ReadInPort()
{
    QByteArray inputData;
    inputData.append(thisPort.readAll());
    dataOutput(inputData);
}
//-----------------------------------------------------------
// Назначение: вызов сигнала для остановки потока
//-----------------------------------------------------------
void comPort::Stop()
{
    qDebug("comPort::stop()");
    //    this->DisconnectPort();
    emit finishedPort();
}
//
QByteArray comPort::writeAndRead(const QByteArray &data)
{
    QByteArray inputData;
    //Записываем в последовательный порт и ждем 50 мс, пока запись не будем произведена
    if(!this->WriteToPort(data))return nullptr;
    thisPort.waitForBytesWritten(50);
    //Засыпаем , ожидая, пока стол обработает данные и ответит
    //    this->thread()->msleep(50);
    //    return thisPort.readAll();
    if(thisPort.waitForReadyRead(50)){
        inputData=thisPort.readAll();
        while (thisPort.waitForReadyRead(10)) {
            inputData+=thisPort.readAll();
        }
    }

    return inputData;
}

//

