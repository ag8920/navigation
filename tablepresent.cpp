#include "tablepresent.h"

TablePreseneter::TablePreseneter(QObject *parent) : QObject(parent)
{
    mainForm=new TableForm;    
    modelTable=new controlTableGRBL;

    createConnect();
}

TablePreseneter::~TablePreseneter()
{
   // emit finished();
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

//void TablePreseneter::AddThread()
//{
//    tableThread=new QThread;
//    modelTable->moveToThread(tableThread);
//    connect(modelTable, &controlTableGRBL::finished,
//            tableThread, &QThread::quit);
//    connect(tableThread, &QThread::finished,
//            modelTable,&controlTableGRBL::deleteLater);
//    connect(modelTable, &controlTableGRBL::finished,
//            tableThread, &QThread::deleteLater);
//    tableThread->start();

//}

