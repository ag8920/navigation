#ifndef ATTITUDEWIDGET_H
#define ATTITUDEWIDGET_H
#include <QWidget>
#include "qcgaugewidget.h"

class attitudeWidget : public QcGaugeWidget//QWidget
{
    Q_OBJECT
public:
    explicit attitudeWidget(QWidget *parent = nullptr);
public slots:
    void setValue(float Roll, float Pitch);
private:
//    QcGaugeWidget * mAttitudeGauge;
    QcNeedleItem * mAttitudeNeedle;
    QcAttitudeMeter *mAttMeter;
};

#endif // ATTITUDEWIDGET_H
