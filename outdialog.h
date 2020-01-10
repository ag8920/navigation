#ifndef OUTDIALOG_H
#define OUTDIALOG_H

#include <QDialog>


typedef union{
    struct{ unsigned short mode:4,int_want:1,
            astrocorr_want:1,sdastrocrr_want:1,
            toBokz_mode:1, pos:1, thdg:1;} bits;
    unsigned short whole;
} structCommandWord;

#define LENGHT_INPMSG 39
typedef struct {
    unsigned long cnt;
    structCommandWord CW;
    unsigned char nPicture;
    double Lat;
    double Lon;
    double H;
    double THdg;
} _structInpMsg;
typedef union{
    _structInpMsg words;
    unsigned char bytes[LENGHT_INPMSG];
}_ansKin;



namespace Ui {
class outDialog;
}

class outDialog : public QDialog
{
    Q_OBJECT

public:
    explicit outDialog(QWidget *parent = nullptr);
    ~outDialog();
    void out();
signals:
    void outputByteArray(const QByteArray &data);
private slots:
    void accept() ;
private:
    Ui::outDialog *ui;
    void writeSettings();
    void readSettings();

    double convertAngle(QString str);
};

#endif // OUTDIALOG_H
