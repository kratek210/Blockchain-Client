#ifndef WALLET_H
#define WALLET_H

#define CHECK_WALLET "http://127.0.0.1:3000/merchant/"+walletId+"/accounts?password="+pass
#define TX_LIST_URL "https://blockchain.info/pl/multiaddr?active=1KwVzCqHaHs4ZUGKrTBTpL6DomFnpDvthT"

#include "httprequest.h"
#include "btcaddress.h"

#include <QJsonObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QSystemTrayIcon>
#include <QJsonValue>


const int SATOSHI_TO_BTC_RATIO = 100000000;

class Wallet : public QObject
{
    Q_OBJECT


public:
    explicit Wallet(QObject* parent, QString login, QString password);
    double getBalance();                            //returns wallet (from all addreses) ballance in satoshi
    QList <BtcAddress*> addrList;       //holds btc addresses
private:

    double balance;                     //holds wallet (All addresses) balance
    HttpRequest httpRequest;            //request to update addrest list and balance
    HttpRequest txRequest;              //request to update tx list
    QJsonDocument jSonDocument;         //holds JSON reply from httpRequest
    QString walletId;                   //holds wallet id from constructor
    QString pass;                       // holds pass from constructor
    QSystemTrayIcon newTxNotify;        //to show notify with new transaction
    void updateBalance(double txVal);   //update ballance
    void setAddressList(QJsonDocument* doc);  //save btcaddress in btcaddr list
    QStringList getAddressList();             //return addresses and balances string list
    void getTx();

private slots:
    void notify(QString btcAddress, double balance, double oldBalance);
    void saveHttpReply(QByteArray data);
    void saveTxList(QByteArray data);

public slots:
    void update();                                                //update all addreses in address list


signals:
    void listUpdate(QStringList, double);      //signal to update addrlist and balance
    void txListReady(QByteArray);
};

#endif // WALLET_H
