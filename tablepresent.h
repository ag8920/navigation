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
    ~TablePreseneter();

signals:
    //void finished();
private:
    TableForm *mainForm;
    controlTableGRBL *modelTable;
    QThread *tableThread;

private:
    void createConnect();    
public slots:
    void showWgt();
    void ConnectedPort(bool arg1);

private:
    bool tableConnect;

private:
    //void AddThread();
};

#endif // TABLEMODEL_H
