#include "tableform.h"
#include "ui_tableform.h"

TableForm::TableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableForm)
{
    ui->setupUi(this);
}

TableForm::~TableForm()
{
    delete ui;
}
