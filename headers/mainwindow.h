#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define LAST_TX_LIMIT 6


#include <QMainWindow>
#include <QTimer>
#include <QClipboard>


#include "wallet.h"
#include "txmodel.h"

const int   REFRESHING_PERIOD = 5000;               //updating balance  in ms

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
    void lastTransaction();                                         //display last 10 txs in dashboard
    TxModel model;                                                  //model for displaying txs
    QVector<QLabel*> labelsTxs;
private slots:
    void updateComboBoxList(QStringList AddrList, double wBalance); //to updateBalance label and combobox
    void updateTx(QByteArray array);
    void on_pushButton_clicked();

};

#endif // MAINWINDOW_H
