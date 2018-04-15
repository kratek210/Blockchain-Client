#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define LAST_TX_LIMIT 6


#include <QMainWindow>
#include <QTimer>
#include <QClipboard>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QSettings>

#include "wallet.h"
#include "txmodel.h"
#include "QrQtcode.h"

const int   REFRESHING_PERIOD = 30000;               //updating balance  in ms

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
    Wallet* wallet;                                                 //pointer to wallet
    TxModel model;                                                  //model for displaying txs
    QVector<QLabel*> labelsTxs;                                     //holds pointers to lastTx labels
    QRCode* code = new QRCode(0, QSize(200, 200), this);
    void createTrayIcon();
    void closeEvent(QCloseEvent* event);
    void lastTransaction();                                         //display last TX_LIMIT txs in dashboard

private slots:
    void updateComboBal(QStringList AddrList, double wBalance);     //to updateBalance balance label and combobox
    void updateTx(QByteArray array);                                //to update tx table and last tx in dashboard
    void on_pushButton_clicked();
    void enableSendButton();                                        //to enable sendbtc button
    void on_btcSendButton_clicked();                                //send button clicked
    void generateQrCode(int index);
    void showHide(QSystemTrayIcon::ActivationReason reason);
    void showHide();
};

#endif // MAINWINDOW_H
