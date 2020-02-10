#ifndef COORDINATEGRIDFORM_H
#define COORDINATEGRIDFORM_H

#include <QWidget>

namespace Ui {
class coordinateGridForm;
}

class coordinateGridForm : public QWidget
{
    Q_OBJECT

public:
    explicit coordinateGridForm(QWidget *parent = nullptr);
    ~coordinateGridForm();

private:
    Ui::coordinateGridForm *ui;
};

#endif // COORDINATEGRIDFORM_H
