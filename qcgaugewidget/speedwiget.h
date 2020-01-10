#ifndef SPEEDWIGET_H
#define SPEEDWIGET_H
#include <QWidget>
#include "qcgaugewidget.h"
#include <QPoint>
class speedwiget : public QcGaugeWidget
{
    Q_OBJECT
public:
    explicit speedwiget(QWidget *parent = nullptr);
public slots:
    void setValue(float value);

//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
public:
//    QPoint m_offset;
private:
    QcNeedleItem *mSpeedNeedle;
};

#endif // SPEEDWIGET_H
