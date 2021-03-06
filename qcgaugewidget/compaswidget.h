#ifndef COMPASWIDGET_H
#define COMPASWIDGET_H

#include <QWidget>
#include "qcgaugewidget.h"
class compasWidget : public QcGaugeWidget
{
    Q_OBJECT
public:
    explicit compasWidget(QWidget *parent = nullptr);

signals:

public slots:
    void setValue(float value);
private:
    QcNeedleItem *mCompassNeedle;
};

#endif // COMPASWIDGET_H
