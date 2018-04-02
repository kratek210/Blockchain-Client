#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
#define CHECK_TX "https://blockchain.info/pl/rawaddr/3D2oetdNuZUqQHPJmcMDDHYoqkyNVsFk9r?limit=5"*/


#include <QMainWindow>
#include <QTimer>
#include "wallet.h"


const int   REFRESHING_PERIOD = 15000;               //updating balance  in ms
const int   SATOSHI_TO_BTC_RATIO = 100000000;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent, QString id, QString walletPass);
    ~MainWindow();

private:

    Ui::MainWindow* ui;
    QString pass;                                                   //wallet pass
    QString walletID;                                               //Blockchain wallet id
    QTimer timer;                                                   //to update data
    Wallet* wallet;
private slots:
    void updateBalanceLabel();                                      //to update balance label;


signals:



};

#endif // MAINWINDOW_H
