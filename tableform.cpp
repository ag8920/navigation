#include "tableform.h"
#include "ui_tableform.h"

#include <QDebug>

TableForm::TableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableForm)
{
    ui->setupUi(this);
    PortSettingsDialog *settingPort = new PortSettingsDialog();

//    connect(ui->settingsButton, &QPushButton::pressed,
//            this, &TableForm::openSettings);

}

TableForm::~TableForm()
{
    delete ui;
}






