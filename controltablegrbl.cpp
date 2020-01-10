#include "controltablegrbl.h"

controlTableGRBL::controlTableGRBL(QObject *parent)
{
    port=new comPort;
    connect(this, &controlTableGRBL::signalSendCommand,
            port, &comPort::WriteToPort);
}

controlTableGRBL::~controlTableGRBL()
{
    delete port;
}

void controlTableGRBL::sendMove(bool Yaxis, bool Zaxis, bool absoluteMove,
                                QString speedYaxis, QString speedZaxis,
                                QString angleYaxis, QString angleZaxis)
{
    QString typeMove=NULL;
    QString sendStr=NULL;

    if(absoluteMove)
        typeMove="G53";
    else typeMove="G91 G01";

    if(Yaxis && Zaxis)
    {
        sendStr=typeMove+" Y"+angleYaxis+" Z"+angleZaxis+"F"+speedZaxis+0x0a+0x0d;
    }
    else if(Yaxis)
    {
        sendStr=typeMove+" Y"+angleYaxis+" F"+speedZaxis+0x0a+0x0d;
    }
    else if(Zaxis)
    {
        sendStr=typeMove+" Z"+angleYaxis+" F"+speedZaxis+0x0a+0x0d;
    }

    if(!sendStr.isEmpty())
        emit signalSendCommand(sendStr.toLocal8Bit());

}

bool controlTableGRBL::ConnectPort(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl)
{
    port->ConnectPort(name,baudrate,DataBits,Parity,StopBits,FlowControl);
    connectPort=port->getIsConnectPort();
    return connectPort;
}

bool controlTableGRBL::DisconnectPort()
{

    port->DisconnectPort();
    connectPort=port->getIsConnectPort();
    return connectPort;
}

bool controlTableGRBL::getConnectPort() const
{
    return connectPort;
}

