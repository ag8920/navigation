#include "attitudewidget.h"
#include <QGridLayout>
attitudeWidget::attitudeWidget(QWidget *parent) : QcGaugeWidget(parent)
{
    this->addBackground(99);
    QcBackgroundItem *bkg = this->addBackground(92);
    bkg->clearrColors();
    bkg->addColor(0.1,Qt::black);
    bkg->addColor(1.0,Qt::darkGray);
    mAttMeter = this->addAttitudeMeter(88);
    mAttitudeNeedle = this->addNeedle(70);
    mAttitudeNeedle->setMinDegree(0);
    mAttitudeNeedle->setMaxDegree(180);
    mAttitudeNeedle->setValueRange(0,180);
    mAttitudeNeedle->setCurrentValue(90);
    mAttitudeNeedle->setColor(Qt::gray);
    mAttitudeNeedle->setNeedle(QcNeedleItem::AttitudeMeterNeedle);
    //this->addGlass(80);
}

void attitudeWidget::setValue(float Roll, float Pitch)
{
    mAttitudeNeedle->setCurrentValue(90-Roll);
    mAttMeter->setCurrentRoll(Roll);
    mAttMeter->setCurrentPitch(Pitch);
}

