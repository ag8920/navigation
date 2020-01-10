#include "speedwiget.h"
#include <QGridLayout>
#include <QMouseEvent>
speedwiget::speedwiget(QWidget *parent)
{

    this->addBackground(99);
    QcBackgroundItem *bkg1 = this->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::darkGray);

    QcBackgroundItem *bkg2 = this->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::darkGray);
    bkg2->addColor(1.0,Qt::black);

    this->addArc(55);
    this->addDegrees(65)->setValueRange(0,80);
    //this->addColorBand(50);


    this->addValues(80)->setValueRange(0,80);

    this->addLabel(70)->setText("m/s");
    QcLabelItem *lab = this->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = this->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,80);
    this->addBackground(7);
    //this->addGlass(88);
}

void speedwiget::setValue(float value)
{
    mSpeedNeedle->setCurrentValue(value);
}

//void speedwiget::mousePressEvent(QMouseEvent *event)
//{
//    event->accept();
//    setCursor(Qt::ClosedHandCursor);
//    if(isWindow())
//        m_offset = event->pos();
//}

//void speedwiget::mouseMoveEvent(QMouseEvent *event)
//{
//    event->accept();
//    if(!isWindow())
//        move(event->globalPos()-m_offset);
//    else
//        move(mapToParent(event->pos()-m_offset));
//}

//void speedwiget::mouseReleaseEvent(QMouseEvent *event)
//{
//    event->accept();
//    m_offset = QPoint();
//    setCursor(Qt::OpenHandCursor);
//}



