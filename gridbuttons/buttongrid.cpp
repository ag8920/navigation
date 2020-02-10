#include "buttongrid.h"
#include <QGridLayout>
#include <QLayout>
#include <qdebug.h>
#include <QDoubleValidator>
#include <QSpacerItem>
#include <QLabel>

buttonGrid::buttonGrid(const QString &xAxisName,const  QString &yAxisName, QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *buttonGridLayout ;//= new QGridLayout;
    createButtons(COUNTBUTTONS);
    buttonGridLayout = createGridButton(COL,ROW,COUNTBUTTONS);
    this->xAxisName = xAxisName;
    this->yAxisName = yAxisName;

    QDoubleValidator *dblv=new QDoubleValidator;
    dblv->setLocale(QLocale::English);
    angleLineEdit = new LineEdit();
    angleLineEdit->setValidator(dblv);
    speedLineEdit = new LineEdit();
    speedLineEdit->setValidator(dblv);
    QHBoxLayout *leLayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    leLayout->addStretch();
    leLayout->addWidget(new QLabel(tr("Угол:")));
    leLayout->addWidget(angleLineEdit);
    leLayout->addStretch();
    leLayout->addWidget(new QLabel(tr("Скорость:")));
    leLayout->addWidget(speedLineEdit);
    leLayout->addStretch();
    mainLayout->addLayout(buttonGridLayout);
    mainLayout->addLayout(leLayout);

    connect(angleLineEdit, &LineEdit::textChanged,
            this, &buttonGrid::inputAngle);
    connect(speedLineEdit, &LineEdit::textChanged,
            this, &buttonGrid::inputSeed);

//    connect(this,&buttonGrid::pressButton,this,&buttonGrid::testpressButton);

    setLayout(mainLayout);

}

buttonGrid::~buttonGrid()
{
}

void buttonGrid::buttonClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    double x=clickedButton->getXAxis();
    double y=clickedButton->getYAxis();
//    qDebug()<<x<<" : "<<y;
    emit pressButton(true, true, true,
                QString::number(speed), QString::number(speed),
                QString::number(y), QString::number(x));
}

void buttonGrid::inputAngle(const QString &text)
{
    changeValueButtons(text.toDouble(),ROW,COL,yAxisName.toUtf8(),xAxisName.toUtf8());
}

void buttonGrid::inputSeed(const QString &text)
{
    setSpeed(text.toDouble());
//    qDebug()<<getSpeed();
}

void buttonGrid::testpressButton(bool Yaxis, bool Zaxis, bool absoluteMove,
                                 QString speedYaxis, QString speedXaxis,
                                 QString angleYaxis, QString angleXaxis)
{
    qDebug()<<Yaxis<<Zaxis<<absoluteMove<<speedYaxis<<speedXaxis<<angleYaxis<<angleXaxis;
}

Button *buttonGrid::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()),this,member);
    return button;
}

void buttonGrid::createButtons(int count)
{
    for (int i=0;i<count;++i){
        angleButtons[i] = createButton(QString::number(i),SLOT(buttonClicked()));

    }
}

void buttonGrid::changeValueButtons(double alfa,int row,int col, const char *yAxis, const char *xAxis )
{

    if(!row || !col) return;

    int startvalrow = row/2-row+1;
    int startvalcol = col/2-col+1;
    double x,y;
    int u=0;
    for (int i=0;i<row;++i)
    {
        y=alfa*(startvalrow+i);
        for(int j=0;j<col;++j){
            x=alfa*(startvalcol+j);
            angleButtons[u]->setText(xAxis +QString::number(x)+", "+yAxis+ QString::number(y));
            angleButtons[u]->setXAxis(x);
            angleButtons[u]->setYAxis(y);
            u++;
        }
    }

}

QGridLayout *buttonGrid::createGridButton(int colTable,int rowTable,int countButtons)
{
    QGridLayout *Layout = new QGridLayout;
    for (int i=1;i<countButtons+1;++i)
    {
        int row = ((countButtons - i) / rowTable) + 3;
        int column = ((i - 1) % colTable) + 2;
        Layout->addWidget(angleButtons[i-1],row,column);
        //qDebug()<<row<<" "<<column;


    }
    return  Layout;
}

double buttonGrid::getSpeed() const
{
    return speed;
}

void buttonGrid::setSpeed(double value)
{
    speed = value;
}

