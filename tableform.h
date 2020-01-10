#ifndef TABLEFORM_H
#define TABLEFORM_H

#include "comport/portsettings/settingsportdialog.h"
#include <QWidget>
#include <QStatusBar>

namespace Ui {
class TableForm;
}

class TableForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableForm(QWidget *parent = nullptr);
    ~TableForm();

signals:
    void openSettings();
    void disconnectPort();
private slots:
public slots:

private:
    Ui::TableForm *ui;
    QStatusBar *statusBar;

};

#endif // TABLEFORM_H
