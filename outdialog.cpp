#include "outdialog.h"
#include "ui_outdialog.h"
#include <QDebug>
#include <QSettings>
outDialog::outDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::outDialog)
{
    //xB0 x27 x22
    ui->setupUi(this);
    ui->lineEditLat->setInputMask("000:00:00");
    ui->lineEditLon->setInputMask("000:00:00");
    ui->lineEditTHdg->setInputMask("000:00:00");
    ui->lineEditShots->setInputMask("000");
    ui->lineEditH->setInputMask("0000.00");
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &outDialog::accept);
    readSettings();
}

outDialog::~outDialog()
{
    delete ui;

}

void outDialog::out()
{
    _ansKin data;
    QByteArray bytedata;
    QDataStream stream(&bytedata,QIODevice::WriteOnly);

    static uint32_t cnt=0;
    cnt++;
    stream.setVersion(QDataStream::Qt_4_3);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    data.words.Lat=convertAngle(ui->lineEditLat->text());
    data.words.Lon=convertAngle(ui->lineEditLon->text());
    data.words.H=ui->lineEditH->text().toDouble();
    data.words.THdg=convertAngle(ui->lineEditTHdg->text());
    data.words.nPicture=ui->lineEditShots->text().toUInt();

    ui->checkBoxSNScor->isChecked()? data.words.CW.bits.int_want=1: data.words.CW.bits.int_want=0;
    ui->checkBoxSDcor->isChecked()? data.words.CW.bits.sdastrocrr_want=1:data.words.CW.bits.sdastrocrr_want=0;
    ui->checkBoxBOKZcor->isChecked()? data.words.CW.bits.astrocorr_want=1:data.words.CW.bits.astrocorr_want=0;
    ui->checkBoxPosval->isChecked()? data.words.CW.bits.pos=1:data.words.CW.bits.pos=0;
    ui->checkBoxThdval->isChecked()? data.words.CW.bits.thdg=1:data.words.CW.bits.thdg=0;
    ui->checkBoxTOBokz->isChecked()? data.words.CW.bits.toBokz_mode=1:data.words.CW.bits.toBokz_mode=0;

    if(ui->comboBoxMode->currentIndex()==0)
        data.words.CW.bits.mode=0;
    else if(ui->comboBoxMode->currentIndex()==1)
        data.words.CW.bits.mode=1;
    else if(ui->comboBoxMode->currentIndex()==2)
        data.words.CW.bits.mode=2;
    else if(ui->comboBoxMode->currentIndex()==3)
        data.words.CW.bits.mode=3;
    else if(ui->comboBoxMode->currentIndex()==4)
        data.words.CW.bits.mode=4;
    else if(ui->comboBoxMode->currentIndex()==5)
        data.words.CW.bits.mode=5;

    stream<<cnt
           <<data.words.CW.whole
           <<data.words.nPicture
           <<data.words.Lat
           <<data.words.Lon
           <<data.words.H
           <<data.words.THdg;
    emit outputByteArray(bytedata);
}

void outDialog::accept()
{
    out();
    writeSettings();
    this->hide();
}

void outDialog::writeSettings()
{
    QSettings settings("settings.ini",QSettings::IniFormat);
    settings.beginGroup("output_value");
    settings.setValue("nShots",ui->lineEditShots->text());
    settings.setValue("Lat", ui->lineEditLat->text());
    settings.setValue("Lon",ui->lineEditLon->text());
    settings.setValue("H",ui->lineEditH->text());
    settings.setValue("THdg",ui->lineEditTHdg->text());
    settings.endGroup();
}

void outDialog::readSettings()
{
    QSettings settings("settings.ini",QSettings::IniFormat);
    settings.beginGroup("output_value");
    ui->lineEditShots->setText(settings.value("nShots","10").toString());
    ui->lineEditLat->setText(settings.value("Lat","55:37:00").toString());
    ui->lineEditLon->setText(settings.value("Lon","37:54:36").toString());
    ui->lineEditH->setText(settings.value("H","160").toString());
    ui->lineEditTHdg->setText(settings.value("THdg","359:59:59").toString());
    settings.endGroup();
}

double outDialog::convertAngle(QString str)
{
    QStringList lst;
    lst=str.split(QRegExp(":"));
    return lst.at(0).toDouble()+(lst.at(1).toDouble()+lst.at(2).toDouble()/60.)/60.;
}




