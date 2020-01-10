#include "compaswidget.h"
#include <QGridLayout>
compasWidget::compasWidget(QWidget *parent) : QcGaugeWidget(parent)
{


    this->addBackground(99);
    QcBackgroundItem *bkg1 = this->addBackground(95);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::darkGray);

    QcBackgroundItem *bkg2 = this->addBackground(90);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::darkGray);
    bkg2->addColor(1.0,Qt::black);

    QcLabelItem *w = this->addLabel(80);
    w->setText("W");
    w->setAngle(0);
    w->setColor(Qt::gray);

    QcLabelItem *n = this->addLabel(80);
    n->setText("N");
    n->setAngle(90);
    n->setColor(Qt::darkBlue);

    QcLabelItem *e = this->addLabel(80);
    e->setText("E");
    e->setAngle(180);
    e->setColor(Qt::gray);

    QcLabelItem *s = this->addLabel(80);
    s->setText("S");
    s->setAngle(270);
    s->setColor(Qt::darkRed);

//    QcLabelItem *deg45 = mCompassGauge->addLabel(76);
//    deg45->setText("45");
//    deg45->setAngle(90+45);
//    deg45->setColor(Qt::white);

//    QcLabelItem *deg135 = mCompassGauge->addLabel(76);
//    deg135->setText("135");
//    deg135->setAngle(180+45);
//    deg135->setColor(Qt::white);


//    QcLabelItem *deg225 = mCompassGauge->addLabel(76);
//    deg225->setText("225");
//    deg225->setAngle(270+45);
//    deg225->setColor(Qt::white);

//    QcLabelItem *deg315 = mCompassGauge->addLabel(76);
//    deg315->setText("315");
//    deg315->setAngle(0+45);
//    deg315->setColor(Qt::white);


    QcDegreesItem *deg = this->addDegrees(70);
    deg->setStep(10);
    deg->setMaxDegree(450);
    deg->setMinDegree(0);
    deg->setColor(Qt::gray);
    QcDegreesItem *deg2 = this->addDegrees(70);
    deg2->setStep(1);
    deg2->setMaxDegree(450);
    deg2->setMinDegree(0);
    deg2->setColor(Qt::gray);
    deg2->setSubDegree(true);

    mCompassNeedle = this->addNeedle(60);
    mCompassNeedle->setNeedle(QcNeedleItem::CompassNeedle);
    mCompassNeedle->setValueRange(0,450);
    mCompassNeedle->setMaxDegree(450);
    mCompassNeedle->setMinDegree(0);
    this->addBackground(7);
    //this->addGlass(90);
    this->setValue(0.);

}

void compasWidget::setValue(float value)
{
    float roatvalue=value+90.;
    mCompassNeedle->setCurrentValue(roatvalue);
}

