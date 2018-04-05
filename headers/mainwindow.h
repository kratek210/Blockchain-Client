#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
#define CHECK_TX "https://blockchain.info/pl/rawaddr/3D2oetdNuZUqQHPJmcMDDHYoqkyNVsFk9r?limit=5"*/


#include <QMainWindow>
#include <QTimer>
#include <QClipboard>

#include "wallet.h"
#include "qjsonmodel.h"

const int   REFRESHING_PERIOD = 25000;               //updating balance  in ms

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
    void updateComboBoxList(QStringList AddrList, double wBalance); //to updateBalance label and combobox
    void updateTx(QByteArray array);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
