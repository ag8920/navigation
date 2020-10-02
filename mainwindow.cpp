#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDataStream>
#include <QLabel>
#include <QLineEdit>

QDataStream &operator>>(QDataStream &stream, _structAnsK &data)
{
    stream >> data.count>>data.statusBII.whole>>data.Tsys>>data.Tunix
        >>data.daytime>>data.day>>data.month>>data.year>>data.DUT1
        >>data.Lat>>data.Lon>>data.H>>data.Ve>>data.Vn>>data.Vu
        >>data.THdg>>data.Roll>>data.Pitch>>data.dVx>>data.dVy>>data.dVz
        >>data.dWx>>data.dWy>>data.dWz>>data.statusSNS.whole>>data.Latsns
        >>data.Lonsns>>data.Hsns>>data.Vesns>>data.Vnsns>>data.Vusns
        >>data.Tgps>>data.nWeekgps>>data.SKOsns>>data.nGlon>>data.nGPS
        >>data.VDop>>data.HDop>>data.statusBokz.whole >>data.TimeZDexp
        >>data.Mornt[0][0]>>data.Mornt[0][1]>>data.Mornt[0][2]
        >>data.Mornt[1][0]>>data.Mornt[1][1]>>data.Mornt[1][2]
        >>data.Mornt[2][0]>>data.Mornt[2][1]>>data.Mornt[2][2]
        >>data.de[0]>>data.de[1]>>data.de[2]
        >>data.Astrocnt1>>data.Astrocnt2>>data.Astrocnt3
        >>data.statusSD.whole>>data.Timesd
        >>data.Lsd>>data.Msd>>data.Nsd>>data.Desd
        >>data.AstroncntSd;
    return stream;
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/icons/icons/wader.png"));

    settingsUdpPort = new settingsDialog(this);
    settingsUdpPort->setWindowTitle(tr("Настройка порта"));
    settingsUdpPort->setWindowIcon(QIcon(":/icons/icons/settings2.png"));

    outputdialog = new outDialog(this);
    outputdialog->setWindowTitle(tr("Отправка данных"));
    outputdialog->setWindowIcon(QIcon(":/icons/icons/send.png"));


    table=new TablePreseneter;

    udp = new udpDrv;
    udpThread=new QThread;

    log = new loger;
    logThread=new QThread;

    tmr=new QTimer;
    tmr->setInterval(1000);
    tmr->start();

    firstpacket=false;

    createWidget();
    createConnect();
    addThread();

    ui->tabWidget->setMovable(true);



    labelStatusTime=new QLabel;
    ui->statusBar->addPermanentWidget(labelStatusTime);
}

MainWindow::~MainWindow()
{
    delete ui;
    logThread->quit();
}


void MainWindow::createWidget()
{
    compas = new compasWidget;
    ui->gridLayout_15->addWidget(compas,0,0);

    attitude = new attitudeWidget;
    ui->gridLayout_15->addWidget(attitude,0,1);

    speedwgt = new speedwiget;
    ui->gridLayout_15->addWidget(speedwgt,0,2);

    ledConnectSNS = new RgbLed(nullptr,Qt::gray);
    ledConnectBOKZ = new RgbLed(nullptr,Qt::gray);
    ledConnectSD = new RgbLed(nullptr,Qt::gray);

    ledSNScorr = new RgbLed(nullptr,Qt::gray);
    ledBOKZcorr = new RgbLed(nullptr,Qt::gray);
    ledSDcorr = new RgbLed(nullptr,Qt::gray);

    ui->formLayoutStatus->addRow(tr("Connect SNS"),ledConnectSNS);
    ui->formLayoutStatus->addRow(tr("Connect BOKZ"),ledConnectBOKZ);
    ui->formLayoutStatus->addRow(tr("Connect SD"),ledConnectSD);

    ui->formLayoutCorr->addRow(tr("SNS correction"),ledSNScorr);
    ui->formLayoutCorr->addRow(tr("BOKZ correction"),ledBOKZcorr);
    ui->formLayoutCorr->addRow(tr("SD correction"),ledSDcorr);

    labelLat=new QLabel("0°0′0″");
    labelLon=new QLabel("0°0′0″");
    labelHeight=new QLabel("0°0′0″");

    labelLatsns=new QLabel("0°0′0″");
    labelLonsns=new QLabel("0°0′0″");
    labelHeightsns=new QLabel("0°0′0″");

    labelTsys=new QLabel("0.");
    labelTunix=new QLabel("0.");
    labelTimeZD=new QLabel("0.");
    labelTimeSD=new QLabel("0.");

    labelBinsMode=new QLabel("-");
    labelBokzMode=new QLabel("-");
    labelSdMode=new QLabel("-");
    labelSNSmode=new QLabel("-");

    labelRoll=new QLabel("0°0′0″");
    labelPitch=new QLabel("0°0′0″");
    labelHeading=new QLabel("0°0′0″");
    labelSpeed=new QLabel("-");

    labelVe = new QLabel("0.");
    labelVn = new QLabel("0.");
    labelVu = new QLabel("0.");

    ui->formLayoutLocation->addRow(tr("Lat: "),labelLat);
    ui->formLayoutLocation->addRow(tr("Lon: "),labelLon);
    ui->formLayoutLocation->addRow(tr("Height: "),labelHeight);

    ui->formLayoutSnsLocation->addRow(tr("Lat_sns: "),labelLatsns);
    ui->formLayoutSnsLocation->addRow(tr("Lon_sns: "),labelLonsns);
    ui->formLayoutSnsLocation->addRow(tr("Height_sns: "),labelHeightsns);

    ui->formLayoutTime->addRow(tr("system time: "),labelTsys);
    ui->formLayoutTime->addRow(tr("unix time: "),labelTunix);
    ui->formLayoutTime->addRow(tr("time BOKZ: "),labelTimeZD);
    ui->formLayoutTime->addRow(tr("time SD: "),labelTimeSD);

    ui->formLayoutMode->addRow(tr("bins mode: "),labelBinsMode);
    ui->formLayoutMode->addRow(tr("sns mode: "),labelSNSmode);
    ui->formLayoutMode->addRow(tr("bokz mode: "),labelBokzMode);
    ui->formLayoutMode->addRow(tr("sd mode: "),labelSdMode);

    ui->formLayoutRollPitch->addRow(tr("Roll: "),labelRoll);
    ui->formLayoutRollPitch->addRow(tr("Pitch: "),labelPitch);
    ui->formLayoutHeading->addRow(tr("Heading: "),labelHeading);
    ui->formLayoutSpeed->addRow(tr("Speed: "),labelSpeed);
    ui->formLayoutSpeed->addRow(tr("Ve: "),labelVe);
    ui->formLayoutSpeed->addRow(tr("vn: "),labelVn);
    ui->formLayoutSpeed->addRow(tr("Vu: "),labelVu);

    ui->actionREC->setEnabled(false);
    ui->actionConnect->setEnabled(false);
    ui->actionOutpack->setEnabled(false);

    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::createConnect()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::Connect);
    connect(ui->actionSettingsPort, &QAction::triggered,settingsUdpPort, &settingsDialog::show );
    connect(settingsUdpPort, &settingsDialog::signalSettginsUpdate, this, &MainWindow::settingsUpdate);
    connect(ui->actionOutpack, &QAction::triggered, outputdialog, &outDialog::show);

    connect(this, &MainWindow::signalInitSocket, udp, &udpDrv::initSocket);
    connect(udp, &udpDrv::signaldataOutput, this, &MainWindow::decode);


    connect(ui->actionREC, &QAction::toggled,this,&MainWindow::recordData);
    connect(this,&MainWindow::signalBeginRecord,log,&loger::start);
    connect(this,&MainWindow::signalStopRecord,log,&loger::CloseFile);
    connect(udp, &udpDrv::signaldataOutput, log, &loger::write);

    connect(tmr,&QTimer::timeout,this,&MainWindow::updateWidget);

    connect(outputdialog, &outDialog::outputByteArray, udp, &udpDrv::WriteToSocket);

    connect(this, &MainWindow::signalDisconnect, udp, &udpDrv::closeSocket);

    connect(ui->actionControlTable, &QAction::triggered,
            table, &TablePreseneter::showWgt);

}

void MainWindow::addThread()
{


    log->moveToThread(logThread);
    connect(log,&loger::finished,
            logThread,&QThread::quit);
    connect(logThread,&QThread::finished,
            log,&loger::deleteLater);
    connect(log,&loger::finished,
            logThread,&QThread::deleteLater);
    logThread->start();



    qDebug()<< QThread::currentThread();
}



void MainWindow::Connect()
{
    static bool connect=false;
    if(!connect){
    emit signalInitSocket(settingsUdpPort->getIPadresReciever(),
                          settingsUdpPort->getIPadresSender(),
                          settingsUdpPort->getPort());
    ui->actionConnect->setIcon(QIcon(":/icons/icons/connect.png"));
    ui->actionOutpack->setEnabled(true);
    ui->actionREC->setEnabled(true);
    ui->actionREC->setIcon(QIcon(":/icons/icons/rec_red.png"));
    connect=true;
    }
    else if(connect){
        emit signalDisconnect();
        ui->actionConnect->setIcon(QIcon(":/icons/icons/disconnect.png"));
        ui->actionConnect->setText(tr("Отключить"));
        ui->actionOutpack->setEnabled(false);
        ui->actionREC->setEnabled(false);
        connect=false;
    }
}

void MainWindow::decode(const QByteArray &datagram)
{
//    _structAnsK data;

    QDataStream stream(datagram);
    stream.setVersion(QDataStream::Qt_4_3);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream>>data;
    firstpacket=true;


}

void MainWindow::updateWidget()
{
    static bool red=false;

    if(ui->actionREC->isChecked() && !red)
    { ui->actionREC->setIcon(QIcon(":/icons/icons/rec_green.png")); red=true;}
    else if(ui->actionREC->isChecked() && red)
    { ui->actionREC->setIcon(QIcon(":/icons/icons/rec_red.png")); red=false;}

    if(firstpacket){
        updateBinsTable(&data);
        updateSNSTable(&data);
        updateBokzTable(&data);
        updateSDTable(&data);

        updateLocationLabel(data.Lat,data.Lon,data.H,data.Latsns,data.Lonsns,data.Hsns);
        updateTimeLabel(data.Tsys,data.Tunix,data.TimeZDexp,data.Timesd);
        updateSpeed(data.Ve,data.Vn,data.Vu);
        updateHeading(data.THdg);
        updateRollPitch(data.Roll,data.Pitch);

        ledConnectBOKZ->statusColor(!data.statusBokz.bits.noConnect);
        ledConnectSNS->statusColor(!data.statusSNS.bits.fault);
        ledConnectSD->statusColor(!data.statusSD.bits.noConnect);

        ledSNScorr->statusColor(data.statusBII.bits.int_mode);
        ledBOKZcorr->statusColor(data.statusBII.bits.bokz_mode);
        ledSDcorr->statusColor(data.statusBII.bits.sd_mode);



        if(data.statusBII.bits.currentMode==0x01)      labelBinsMode->setText(tr("<b>Align GK<\b>"));
        else if(data.statusBII.bits.currentMode==0x02) labelBinsMode->setText(tr("<b>Align ZK<\b>"));
        else if(data.statusBII.bits.currentMode==0x03) labelBinsMode->setText(tr("<b>Align BOKZ<\b>"));
        else if(data.statusBII.bits.currentMode==0x04) labelBinsMode->setText(tr(" <font color=#439400><b>Navigation<\b><\font>"));
        else if(data.statusBII.bits.currentMode==0x00) labelBinsMode->setText("<font color:red;><b>Wait<\b><\font>");

        if(data.statusBokz.bits.currentMode==0x01) labelBokzMode->setText(tr("<b>NO<\b>"));
        else if(data.statusBokz.bits.currentMode==0x02) labelBokzMode->setText(tr("<b>TO<\b>"));
        else if(data.statusBokz.bits.currentMode==0x03) labelBokzMode->setText(tr("<font color=#439400><b>Navigation<\b><\font>"));
        else if(data.statusBokz.bits.currentMode==0x00) labelBokzMode->setText(tr("<b>Wait<\b>"));

        if(data.statusSD.bits.currentMode==1) labelSdMode->setText(tr("<b>NO<\b>"));
        else if(data.statusSD.bits.currentMode==1) labelSdMode->setText(tr(" <font color=#439400><b>Navigation<\b><\font>"));
        else if(data.statusSD.bits.currentMode==0) labelSdMode->setText(tr("<b>Wait<\b>"));

        if(data.statusSNS.bits.navigationMode) labelSNSmode->setText(tr("<font color=#439400><b>Navigation<\b><\font>"));
        else labelSNSmode->setText(tr("<b>Wait<\b>"));
    }

    time=QDateTime::currentDateTime();
    labelStatusTime->setText(time.toString()+"\tUnix: "+QString::number(time.toMSecsSinceEpoch()));
}

void MainWindow::recordData()
{
    if(ui->actionREC->isChecked())
    {
        emit signalBeginRecord();
        ui->actionREC->setText(tr("остановить запись"));
    }
    else
    {
        emit signalStopRecord();
        ui->actionREC->setText(tr("начать запись"));
        ui->actionREC->setIcon(QIcon(":/icons/icons/rec_red.png"));
    }
}

void MainWindow::settingsUpdate()
{
    ui->actionConnect->setEnabled(true);
}

void MainWindow::updateBinsTable(const _structAnsK *data)
{
    QList<QString> *lst=new QList<QString>;
    lst->append(QString::number(data->count));
    lst->append(QString::number(data->statusBII.whole));
    lst->append(QString::number(data->Tsys));
    lst->append(QString::number(data->Tunix,'g',12));
    lst->append(QString::number(data->daytime));
    lst->append(QString::number(data->day));
    lst->append(QString::number(data->month));
    lst->append(QString::number(data->year));
    lst->append(QString::number(data->DUT1));
    lst->append(QString::number(data->Lat));
    lst->append(QString::number(data->Lon));
    lst->append(QString::number(data->H));
    lst->append(QString::number(data->Ve));
    lst->append(QString::number(data->Vn));
    lst->append(QString::number(data->Vu));
    lst->append(QString::number(data->THdg));
    lst->append(QString::number(data->Roll));
    lst->append(QString::number(data->Pitch));
    lst->append(QString::number(data->dVx));
    lst->append(QString::number(data->dVy));
    lst->append(QString::number(data->dVz));
    lst->append(QString::number(data->dWx));
    lst->append(QString::number(data->dWy));
    lst->append(QString::number(data->dWz));
    createTable(ui->tableWidgetBins,lst);
    delete lst;
}

void MainWindow::updateSNSTable(const _structAnsK *data)
{
    QList<QString> *lst=new QList<QString>;
    lst->append(QString::number(data->statusSNS.whole));
    lst->append(QString::number(data->Latsns));
    lst->append(QString::number(data->Lonsns));
    lst->append(QString::number(data->Hsns));
    lst->append(QString::number(data->Vesns));
    lst->append(QString::number(data->Vnsns));
    lst->append(QString::number(data->Vusns));
    lst->append(QString::number(data->Tgps));
    lst->append(QString::number(data->nWeekgps));
    lst->append(QString::number(data->SKOsns));
    lst->append(QString::number(data->nGlon));
    lst->append(QString::number(data->nGPS));
    lst->append(QString::number(data->VDop));
    lst->append(QString::number(data->HDop));
    createTable(ui->tableWidgetSNS,lst);
    delete  lst;
}

void MainWindow::updateBokzTable(const _structAnsK *data)
{
    QList<QString> *lst=new QList<QString>;
    lst->append(QString::number(data->statusBokz.whole));
    lst->append(QString::number(data->TimeZDexp));
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j)
            lst->append(QString::number(data->Mornt[i][j]));
        lst->append(QString::number(data->de[i]));
    }

    lst->append(QString::number(data->Astrocnt1));
    lst->append(QString::number(data->Astrocnt2));
    lst->append(QString::number(data->Astrocnt3));
    createTable(ui->tableWidgetBOKZ,lst);
    delete  lst;
}

void MainWindow::updateSDTable(const _structAnsK *data)
{
       QList<QString> *lst=new QList<QString>;
       lst->append(QString::number(data->statusSD.whole));
       lst->append(QString::number(data->Timesd));
       lst->append(QString::number(data->Lsd));
       lst->append(QString::number(data->Msd));
       lst->append(QString::number(data->Nsd));
       lst->append(QString::number(data->Desd));
       lst->append(QString::number(data->AstroncntSd));
       createTable(ui->tableWidgetSD,lst);
       delete  lst;
}




void MainWindow::createTable(QTableWidget *wgt, QList<QString> *map)
{
    for(int i=0;i<map->count();++i)
    {
        if(i>wgt->rowCount()) break;
        QTableWidgetItem *item=new QTableWidgetItem;
        item->setText(map->at(i));
        wgt->setItem(i,0,item);

    }
    //wgt->resizeColumnsToContents();
}

void MainWindow::updateLocationLabel(double Lat, double Lon, double H, double Latsns, double Lonsns, double Hsns)
{
    labelLat->setText(deg2String(Lat));
    labelLon->setText(deg2String(Lon));
    labelHeight->setText(QString::number(H));
    labelLatsns->setText(deg2String(Latsns));
    labelLonsns->setText(deg2String(Lonsns));
    labelHeightsns->setText(QString::number(Hsns));
}

void MainWindow::updateTimeLabel(double Tsys, double Tunix, double TimeZD, double TimeSD)
{
    labelTsys->setText(QString::number(Tsys,'g',12));
    labelTunix->setText(QString::number(Tunix,'g',12));
    labelTimeZD->setText(QString::number(TimeZD,'g',12));
    labelTimeSD->setText(QString::number(TimeSD,'g',12));
}

void MainWindow::updateRollPitch(double Roll, double Pitch)
{
    labelRoll->setText(deg2String(Roll));
    labelPitch->setText(deg2String(Pitch));
    attitude->setValue(Roll,Pitch);
}

void MainWindow::updateHeading(double Heading)
{
    labelHeading->setText(deg2String(Heading));
    compas->setValue(Heading);
}

void MainWindow::updateSpeed(double Ve, double Vn, double Vu)
{
    double speed=0;
    speed=sqrt(pow(Ve,2)+pow(Vn,2)+pow(Vu,2));
    labelSpeed->setText(QString::number(speed,'g',2));
    labelVe->setText(QString::number(Ve,'g',2));
    labelVn->setText(QString::number(Vn,'g',2));
    labelVu->setText(QString::number(Vu,'g',2));
    speedwgt->setValue(speed);
}


QString MainWindow::deg2String(double deg)
{
    if(deg==0.)
        return ((tr(" 0°0′0″")));
    double degree, rawMinute;
    double minute,second;
    int dec_deg,dec_min,dec_sec;
    rawMinute=std::modf(deg,&degree);
    rawMinute*=60;
    second=std::modf(rawMinute,&minute);
    second*=60;
    dec_sec=ceil(second);
    dec_min=ceil(minute);
    dec_deg=ceil(degree);
    if(dec_sec>=60)
    {
        dec_min++;
        dec_sec-=60;
    }
    if(dec_min>=60)
    {
        dec_deg++;
        dec_min-=60;
    }

    return (tr("%1°%2′%3″").arg(dec_deg).arg(dec_min).arg(dec_sec));
}




