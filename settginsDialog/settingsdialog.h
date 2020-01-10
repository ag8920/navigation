#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT
    QString IPadresSender;
    QString IPadresreceiver;
    quint16 Port;
public:
    explicit settingsDialog(QWidget *parent = nullptr);
    ~settingsDialog();
    QString getIPadresSender() const;
    QString getIPadresReciever() const;
    quint16 getPort() const;

signals:
    void outSettings(const QString &IP, const QString &Port);
    void signalSettginsUpdate();
public slots:
    void accept();
private:
    Ui::settingsDialog *ui;
    void readSettings();
    void writeSettings();
};

#endif // SETTINGSDIALOG_H
