#include "outdialog.h"
#include "ui_outdialog.h"

outDialog::outDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::outDialog)
{
    ui->setupUi(this);
}

outDialog::~outDialog()
{
    delete ui;
}
