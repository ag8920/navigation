#include "udpdrv.h"
#include <QThread>


udpDrv::udpDrv(QObject *parent)
{

}

udpDrv::~udpDrv()
{
    emit finished();
}

void udpDrv::process()
{
    qDebug()<< QThread::currentThread();
}

void udpDrv::initSocket(QString ipReciev,QString ipSend,quint16 port)
{

    qDebug()<<"ipSender="<<ipSend;
    qDebug()<<"ipReciever="<<ipReciev;
    udpSocket = new QUdpSocket;

    setIpAddrReceiver(QHostAddress(ipReciev));
    setIpAddrSender(QHostAddress(ipSend));
    setPort(port);

    if(udpSocket->bind(getIpAddrReceiver(),getPort()))
        qDebug()<<"socket bind = true";
    else
        qDebug()<<"socket bins = false";
    connect(udpSocket,&QUdpSocket::readyRead,this,&udpDrv::ReadInSocket);
}

void udpDrv::closeSocket()
{
    delete udpSocket;
}

void udpDrv::WriteToSocket(const QByteArray &datagram)
{
    udpSocket->writeDatagram(datagram,getIpAddrSender(),getPort());
}

void udpDrv::ReadInSocket()
{
    QByteArray datagram;
    do {
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
    } while (udpSocket->hasPendingDatagrams());

    signaldataOutput(datagram);

}

quint16 udpDrv::getPort() const
{
    return port;
}

void udpDrv::setPort(const quint16 &value)
{
    port = value;
}

void udpDrv::setIpAddrSender(const QHostAddress &value)
{
    ipAddrSender = value;
}

void udpDrv::setIpAddrReceiver(const QHostAddress &value)
{
    ipAddrReceiver = value;
}

QHostAddress udpDrv::getIpAddrSender() const
{
    return ipAddrSender;
}
QHostAddress udpDrv::getIpAddrReceiver() const
{
    return ipAddrReceiver;
}
