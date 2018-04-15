#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class settingsWindow;
}

class settingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit settingsWindow(QWidget* parent = 0);
    ~settingsWindow();
    void setHost(QString host);
    void setPort(int port);
    void setRefresh(int refresh);
    void setMaxTx(int maxTxs);

private:
    Ui::settingsWindow* ui;



private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // SETTINGSWINDOW_H
