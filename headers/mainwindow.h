#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define CHECK_BALANCE_URL "http://127.0.0.1:3000/merchant/"+walletID+"/balance?password="+pass
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
    QString pass;           //wallet pass
    QString walletID;       //Blockchain wallet id
    QTimer timer;           //to update data
    HttpRequest request[OBJECTS_ARRAY_SIZE];    //objects array for http requests
    QString dataStr[OBJECTS_ARRAY_SIZE];        //holds http request data as String
    QByteArray dataArray[OBJECTS_ARRAY_SIZE];   //holds http request data as ByteArray
    QJsonDocument jSonData[OBJECTS_ARRAY_SIZE]; //holds Json response
    QStringList btcAdresses;                    //holds btc adress
    double btcBalance;                          //holds actual btc balance


    void updateBalance();                       //func to update btc balance
    void recentTxs();                           //func to get last = LAST_TRANSACTION_LIMIT transsactions
    void getWalletAddresses();                  //func to get all wallet btc addresses

private slots:

    void saveReqData(QByteArray data_);         //slot to recive data from HttpRequest class
    void update();                              //slot to update data every REFRESHING_PERIOD ms

};

#endif // MAINWINDOW_H
