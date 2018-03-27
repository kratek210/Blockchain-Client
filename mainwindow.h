#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    explicit MainWindow(QWidget *parent,QString id, QString walletPass);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QString pass;
    QString walletID;
};

#endif // MAINWINDOW_H
