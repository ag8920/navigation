#ifndef MBUTTON_H
#define MBUTTON_H

#include <QPushButton>

class mButton : public QPushButton
{
    Q_OBJECT
public:
    mButton(const QString &text,QWidget *parent=nullptr);

    double getXAxis() const;
    void setXAxis(double value);

    double getYAxis() const;
    void setYAxis(double value);

private:
    double xAxis;
    double yAxis;
};

#endif // MBUTTON_H
