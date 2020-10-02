#include "controltablegrbl.h"

controlTableGRBL::controlTableGRBL(QObject *parent)
{
    port=new comPort;
    connect(this, &controlTableGRBL::signalSendCommand,
            port, &comPort::WriteToPort);

    connect(port, &comPort::boolConnectedPort, this, &controlTableGRBL::portConnected);
    connect(this, &controlTableGRBL::ConnectPort, port, &comPort::ConnectPort);
    connect(this, &controlTableGRBL::DisconnectPort, port, &comPort::DisconnectPort);
    addThread();
}

controlTableGRBL::~controlTableGRBL()
{
    delete port;
}

void controlTableGRBL::sendMove(bool Xaxis,
                                bool Yaxis,
                                bool Zaxis,
                                bool absoluteMove,
                                QString speed,
                                QString angleXaxis,
                                QString angleYaxis,
                                QString angleZaxis)
{
    qDebug()<<"Model Table thread : "<< QThread::currentThread();
    QString typeMove=NULL;
    QString sendStr=NULL;

    if(absoluteMove)
        typeMove="G53 G01";
    else typeMove="G91 G01";

    sendStr=typeMove;
    if(Xaxis) sendStr+= " X"+angleXaxis;
    if(Yaxis) sendStr+= " Y"+angleYaxis;
    if(Zaxis) sendStr+= " Z"+angleZaxis;
    sendStr+= " F"+speed+0x0a+0x0d;

    if(!sendStr.isEmpty())
        emit signalSendCommand(sendStr.toLocal8Bit());

}

/*
bool controlTableGRBL::ConnectPort(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl)
{
    port->ConnectPort(name,baudrate,DataBits,Parity,StopBits,FlowControl);
    connectPort=port->getIsConnectPort();
    //emit portConnected(connectPort);
    return connectPort;
}

bool controlTableGRBL::DisconnectPort()
{

    port->DisconnectPort();
    connectPort=port->getIsConnectPort();
    //emit portConnected(connectPort);
    return connectPort;
}

*/

void controlTableGRBL::addThread()
{
    ComPortThread = new QThread;
    port->moveToThread(ComPortThread);
    port->thisPort.moveToThread(ComPortThread);
    connect(ComPortThread,&QThread::started,
            port,&comPort::processPort);
    connect(port,&comPort::finishedPort,
            ComPortThread,&QThread::quit);
    connect(ComPortThread,&QThread::finished,
            port,&comPort::deleteLater);
    connect(port,&comPort::finishedPort,
            ComPortThread,&QThread::deleteLater);
    ComPortThread->start(QThread::TimeCriticalPriority);
}

bool controlTableGRBL::getConnectPort() const
{
    return connectPort;
}

