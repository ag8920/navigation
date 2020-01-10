#ifndef OUTDIALOG_H
#define OUTDIALOG_H

#include <QDialog>

namespace Ui {
class outDialog;
}

class outDialog : public QDialog
{
    Q_OBJECT

public:
    explicit outDialog(QWidget *parent = nullptr);
    ~outDialog();

private:
    Ui::outDialog *ui;
};

#endif // OUTDIALOG_H
