#ifndef BUTTONGRID_H
#define BUTTONGRID_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

#include "mbutton.h"

typedef mButton Button;
typedef QLineEdit LineEdit;

#define COUNTBUTTONS 25
#define COL 5
#define ROW 5

class buttonGrid : public QWidget
{
    Q_OBJECT

public:
    buttonGrid(const QString &xAxisName = "X", const QString &yAxisName="Y", QWidget *parent = nullptr);
    ~buttonGrid();

    double getSpeed() const;
    void setSpeed(double value);
signals:
    void pressButton(bool Xaxis,
                     bool Yaxis,
                     bool Zaxis,
                     bool absoluteMove,
                     QString speed,
                     QString angleXaxis,
                     QString angleYaxis,
                     QString angleZaxis);
private slots:
    void buttonClicked();
    void inputAngle(const QString &text);
    void inputSeed(const QString &text);

    void testpressButton(bool Xaxis, bool Yaxis, bool Zaxis, bool absoluteMove,
                          QString speedYaxis, QString speedZaxis,
                          QString angleYaxis, QString angleZaxis);

    void clickedBtnZplus();
    void clickedBtnZminus();
    void clickedBtnZnull();
private:
    Button *createButton(const QString &text, const char *member);
     void createButtons(int count);
     void changeValueButtons(double alfa, int row, int col, const char *yAxis="Y", const char *xAxis="X");
    QGridLayout *createGridButton(int colTable, int rowTable, int countButtons);


    LineEdit *angleLineEdit;
    LineEdit *speedLineEdit;
    Button *angleButtons[COUNTBUTTONS];

    LineEdit *ZangleLineEdit;
    QPushButton *btnZplus;
    QPushButton *btnZminus;
    QPushButton *btnZnull;
    double speed;
    QString xAxisName;
    QString yAxisName;

};
#endif // BUTTONGRID_H
