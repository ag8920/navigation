#ifndef TABLEFORM_H
#define TABLEFORM_H

#include "comport/portsettings/settingsportdialog.h"
#include <QWidget>
#include <QStatusBar>

namespace Ui {
class TableForm;
}
enum typeMove {
    relativeMove,
    absoluteMove

};
enum axisMove{
    YaxisMove=1,
    ZaxisMove,
    YZaxisMove
};

class TableForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableForm(QWidget *parent = nullptr);
    ~TableForm();

signals:
    void disconnectPort();
    void ConnectPort(QString name, int baudrate, int DataBits,int Parity,
                     int StropBits,int FlowConrol);

    void pressMoveButton(bool Yaxis, bool Zaxis, bool absoluteMove,
                         QString speedYaxis, QString speedZaxis,
                         QString angleYaxis, QString angleZaxis);
private slots:
    void fillPortsInfo();
    void checkCustomBaudRatePolicy(int idx);
    void clickedUpButton();
    void clickedDownButton();
    void clickedLeftButton();
    void clickedRightButton();
    void clickedHomeButton();
    void setTypeMove();

public slots:
    void clickedConnectButton();
    void ConnectedPort(bool arg1);


private:
    Ui::TableForm *ui;
    QStatusBar *statusBar;

    void fillBaudRateParametres();
    bool isConnectPort;

    QString strAngleYaxis;
    double dAngleYaxis;

    QString strAngleZaxis;
    double dAngleZaxis;

    QString strSpeedYaxis;
    double dSpeedYaxis;

    QString strSpeedZaxis;
    double dSpeedZaxis;

    typeMove move;
    axisMove typeAxisMove;




};

#endif // TABLEFORM_H
