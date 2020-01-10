#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>

class TableModel : public QObject
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);

signals:

};

#endif // TABLEMODEL_H
