#ifndef UDPDRV_H
#define UDPDRV_H
#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>

class udpDrv : public QObject
{
    Q_OBJECT
public:
    explicit udpDrv(QObject *parent=nullptr);
    ~udpDrv();
    void process();

    QHostAddress getIpAddrReceiver() const;
    QHostAddress getIpAddrSender() const;

    inline void setIpAddrReceiver(const QHostAddress &value);
    inline void setIpAddrSender(const QHostAddress &value);

    inline quint16 getPort() const;
    inline void setPort(const quint16 &value);

signals:
    void signaldataOutput(const QByteArray &datagram);
    void finished();

public slots:
    void initSocket(QString ipReciev, QString ipSend, quint16 port);
    void closeSocket();
    void WriteToSocket(const QByteArray &datagram);
    void ReadInSocket();

private:
    QUdpSocket *udpSocket;
    QHostAddress ipAddrReceiver;
    QHostAddress ipAddrSender;
    quint16 port;
};

#endif // UDPDRV_H
