#ifndef TABLEFORM_H
#define TABLEFORM_H

#include "comport/portsettings/settingsportdialog.h"
#include <QWidget>
#include <QStatusBar>

namespace Ui {
class TableForm;
}

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

private slots:
    void fillPortsInfo();
    void checkCustomBaudRatePolicy(int idx);

public slots:
    void clickedConnectButton();
    void ConnectedPort(bool arg1);

private:
    Ui::TableForm *ui;
    QStatusBar *statusBar;

    void fillBaudRateParametres();
    bool isConnectPort;


};

#endif // TABLEFORM_H
