#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define CHECK_WALLET_BALANCE_URL "http://127.0.0.1:3000/merchant/"+walletID+"/balance?password="+pass
#define CHECK_ADDRESS_BALANCE_URL "https://blockchain.info/q/addressbalance/"+btcAdresses[i]+"?confirmations=2"
#define LIST_WALLET_ADRESSES "http://localhost:3000/merchant/"+walletID+"/accounts?password="+pass
#define CHECK_TX "https://blockchain.info/pl/rawaddr/3D2oetdNuZUqQHPJmcMDDHYoqkyNVsFk9r?limit=5"


#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonValue>
#include "headers/httprequest.h"

const double SATOSHI_TO_BTC = 100000000;    //to convert reply from satoshi to BTC
const int    LAST_TRANSACTION_LIMIT = 5;    //recent transactions shown in dashboar
const int   OBJECTS_ARRAY_SIZE = 5;         //array size of objects HttpRequest and data buffers
const int   REFRESHING_PERIOD = 1000;       //updating balance and tx period in ms
const int   MAX_ADDRESES_LIMIT = 10;        //adding limit to HttpRequest array size
enum
{
    ADDR = 0,
    BALANCE = 1,
    TXS = 2,
};                                           //to index arrays


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
    HttpRequest request[OBJECTS_ARRAY_SIZE];                        //objects array for http requests
    QString dataStr[OBJECTS_ARRAY_SIZE];                            //holds wallet http reply data as String
    QByteArray dataArray[OBJECTS_ARRAY_SIZE];                       //holds wallet http reply data as ByteArray
    QJsonDocument jSonData[OBJECTS_ARRAY_SIZE];                     //holds wallet http reply Json response
    QStringList btcAdresses;                                        //holds btc adresses
    QStringList btcLabels;                                          //holds labels for addresses
    double btcBalance;                                              //holds actual wallet btc balance
    QVector<double> addrBalance;                                    //holds one adddress balance

    void updateBalance();                       //func to update wallet btc balance
    void updateAddrBalance();                   //func to update one adrees balance
    void recentTxs();                           //func to get last = LAST_TRANSACTION_LIMIT transsactions
    void getWalletAddrAndBalance();             //func to get all wallet btc addresses ,labels and balance

private slots:

    void saveReqData(QByteArray data_);               //slot to recive data from HttpRequest class (WALLET)
    void update();                                    //slot to update data every REFRESHING_PERIOD ms
    void ballanceChanged(QString addr);               //when balance changed sound and notify & show tx address

signals:

    void addrBalHasChange(QString addr);              //signal when addr balance changed


};

#endif // MAINWINDOW_H
