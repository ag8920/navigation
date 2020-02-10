#include "mbutton.h"

mButton::mButton(const QString &text, QWidget *parent):
    xAxis(0),yAxis(0)
{
    setText(text);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
}

double mButton::getXAxis() const
{
    return xAxis;
}

void mButton::setXAxis(double value)
{
    xAxis = value;
}

double mButton::getYAxis() const
{
    return yAxis;
}

void mButton::setYAxis(double value)
{
    yAxis = value;
}

