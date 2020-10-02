#include "tablepresent.h"

TablePreseneter::TablePreseneter(QObject *parent) : QObject(parent)
{
    mainForm=new TableForm;    
    modelTable=new controlTableGRBL;

    createConnect();
}
void TablePreseneter::createConnect()
{
     connect(mainForm, &TableForm::ConnectPort,
            modelTable, &controlTableGRBL::ConnectPort);
     connect(mainForm, &TableForm::disconnectPort,
             modelTable, &controlTableGRBL::DisconnectPort);
     connect(modelTable, &controlTableGRBL::portConnected,
             this, &TablePreseneter::ConnectedPort);
     connect(modelTable, &controlTableGRBL::portConnected,
             mainForm, &TableForm::ConnectedPort);

     connect(mainForm, &TableForm::pressMoveButton,
             modelTable, &controlTableGRBL::sendMove);
}


void TablePreseneter::showWgt()
{
    mainForm->show();
}

void TablePreseneter::ConnectedPort(bool arg1)
{
    tableConnect=arg1;
}

