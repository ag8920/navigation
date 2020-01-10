#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QWidget>
#include "tableform.h"
#include "comport/portsettings/settingsportdialog.h"
#include "controltablegrbl.h"
class TablePreseneter : public QObject
{
    Q_OBJECT
public:
    explicit TablePreseneter(QObject *parent = nullptr);

signals:

private:
    TableForm *mainForm;
    PortSettingsDialog *settingsForm;
    controlTableGRBL *modelTable;

private:
    void createConnect();
    void openPort();
    void closePort();
public slots:
    void showWgt();

private:
    bool tableConnect;
};

#endif // TABLEMODEL_H
