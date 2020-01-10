#ifndef CONTROLTABLEGRBL_H
#define CONTROLTABLEGRBL_H
#include <QObject>
#include "comport/comport.h"
class controlTableGRBL:public QObject
{
    Q_OBJECT
signals:
    void signalSendCommand(const QByteArray &cmd);
public:
    explicit controlTableGRBL(QObject *parent=nullptr);
    ~controlTableGRBL();
    comPort *port;
    bool getConnectPort() const;

public slots:
    void sendMove(bool Yaxis=false,bool Zaxis=false, bool absoluteMove=false,
                  QString speedYaxis="",
                  QString speedZaxis="",
                  QString angleYaxis="",
                  QString angleZaxis="");
    bool ConnectPort(QString name,int baudrate,
                     int DataBits,int Parity,
                     int StopBits,int FlowControl);
    bool DisconnectPort();
private:
    bool connectPort;
};

#endif // CONTROLTABLEGRBL_H
