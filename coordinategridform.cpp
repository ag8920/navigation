#include "coordinategridform.h"
#include "ui_coordinategridform.h"

coordinateGridForm::coordinateGridForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::coordinateGridForm)
{
    ui->setupUi(this);
}

coordinateGridForm::~coordinateGridForm()
{
    delete ui;
}
