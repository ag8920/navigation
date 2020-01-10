#include "mainwindow.h"
#include "tableform.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    TableForm w;

    QFile file(":style.qss");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    qApp->setStyleSheet(strCSS);

    w.show();

    return a.exec();
}
