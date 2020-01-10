#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QTimer>
#include "settginsDialog/settingsdialog.h"
#include "udpdrv.h"
#include "qcgaugewidget/compaswidget.h"
#include "qcgaugewidget/attitudewidget.h"
#include "qcgaugewidget/speedwiget.h"
#include "ledlamp/rgbled.h"
#include "loger/loger.h"
#include "outdialog.h"
#include "dynamicFont/dynamicfontsizelabel.h"
#include "dynamicFont/dynamicfontsizepushbutton.h"
#include "tablepresent.h"

typedef union {
    struct {unsigned short currentMode:2,noConnect:1, fault:1, trackingSuccel:1, apriorsuccess:1, failUSD:1;} bits;
    unsigned short whole;
} structStatusMcBokz;

typedef union {
    struct{unsigned short navigationMode:1, validTime:1,fault:1; } bits;
    unsigned short whole;
} structStatusSNS;

typedef union {
    struct{unsigned short currentMode:2, noConnect:1, fault:1, solar:1, modeCalcDirr:1, measureSucces:1; } bits;
    unsigned short whole;
} structStatusSD;

typedef union {
    struct{unsigned short currentMode:3, int_mode:1, bokz_mode:1, sd_mode:1, faultBII:1, faultQwork:1;} bits;
    unsigned short whole;
} structStatusBII;
#define LENGHT_ANSSTRUCT 322 //326
typedef struct
{
    //параметры БИНС
    uint32_t count;
    structStatusBII statusBII;
    double Tsys;
    double Tunix; //время в микросекундах от 0ч:0мин:0с 01.01.1970г.

    double daytime;
    unsigned short day;
    unsigned short month;
    unsigned short year;
    double DUT1;

    double Lat;
    double Lon;
    double H;
    double Ve;
    double Vn;
    double Vu;
    double THdg;
    double Roll;
    double Pitch;

    //параметры БИИ
    float dVx;
    float dVy;
    float dVz;
    float dWx;
    float dWy;
    float dWz;

    //параметры СНС
    structStatusSNS statusSNS;
    double Latsns;
    double Lonsns;
    double Hsns;
    double Vesns;
    double Vnsns;
    double Vusns;
    double Tgps;
    signed short nWeekgps;
    float SKOsns;
    unsigned char nGlon;
    unsigned char nGPS;
    float VDop;
    float HDop;

    //параметры БОКЗ
    structStatusMcBokz statusBokz;
    double TimeZDexp;
    float Mornt[3][3];
    double de[3];
    unsigned short Astrocnt1;
    unsigned short Astrocnt2;
    unsigned short Astrocnt3;

    //параметры СД
    structStatusSD statusSD;
    double Timesd;
    float Lsd;
    float Msd;
    float Nsd;
    double Desd;
    unsigned short AstroncntSd;

    // //счетчики для синхронизаций
    // double Tunix; //время в формате unix
    // dword  TickCount;
}_structAnsK;
//extern _structAnsK ansK;










namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void signalInitSocket(QString ipAddrReciever,QString ipAddrSender, quint16 port);
    void signalBeginRecord();
    void signalStopRecord();
    void signalDisconnect();
public slots:
    void Connect();
    void decode(const QByteArray &datagram);
    void updateWidget();
    void recordData();
    void settingsUpdate();
private:
    Ui::MainWindow *ui;

    void createWidget();
    void createConnect();
    void addThread();
    void updateBinsTable(const _structAnsK *data);
    void updateSNSTable(const _structAnsK *data);
    void updateBokzTable(const _structAnsK *data);
    void updateSDTable(const _structAnsK *data);
    void createTable(QTableWidget *wgt, QList<QString> *map);

    void updateLocationLabel(double Lat,double Lon,double H, double Latsns,double Lonsns,double Hsns);
    void updateTimeLabel(double Tsys, double Tunix,double TimeZD,double TimeSD);
    void updateRollPitch(double Roll, double Pitch);
    void updateHeading(double Heading);
    void updateSpeed(double Ve,double Vn,double Vu);



    QString deg2String(double deg);
public:
    friend QDataStream &operator>>(QDataStream &stream,_structAnsK &data );

private:
   settingsDialog *settingsUdpPort;
   udpDrv *udp;
   QThread *udpThread;
   loger *log;
   QThread *logThread;
   outDialog *outputdialog;
   compasWidget *compas;
   attitudeWidget *attitude;
   speedwiget *speedwgt;
   QTimer *tmr;
   TablePreseneter *table;

   _structAnsK data;

   RgbLed *ledConnectSNS;
   RgbLed *ledConnectBOKZ;
   RgbLed *ledConnectSD;
   RgbLed *ledSNScorr;
   RgbLed *ledBOKZcorr;
   RgbLed *ledSDcorr;

   QLabel *labelLat;
   QLabel *labelLon;
   QLabel *labelHeight;

   QLabel *labelLatsns;
   QLabel *labelLonsns;
   QLabel *labelHeightsns;

   QLabel *labelTsys;
   QLabel *labelTunix;
   QLabel *labelTimeZD;
   QLabel *labelTimeSD;

   QLabel *labelBinsMode;
   QLabel *labelSNSmode;
   QLabel *labelBokzMode;
   QLabel *labelSdMode;

   QLabel *labelRoll;
   QLabel *labelPitch;
   QLabel *labelHeading;
   QLabel *labelSpeed;
   QLabel *labelVe;
   QLabel *labelVu;
   QLabel *labelVn;

   bool firstpacket;

};

#endif // MAINWINDOW_H
