#ifndef WALLET_H
#define WALLET_H

#define CHECK_WALLET "http://35.196.109.84:3000/merchant/"+walletId+"/accounts?password="+pass
//#define TX_LIST_URL "https://blockchain.info/pl/multiaddr?active="
#define TX_LIST_URL "https://blockchain.info/pl/multiaddr?active=1Kr6QSydW9bFQG1mXiPNNu6WpJGmUa9i1g"
#define SEND_BTC_URL "http://35.196.109.84:3000/merchant/"+walletId+"/payment?password="+pass+"&to="+reciverAddr+"&amount="

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


    double getBalance();                                    //returns wallet (from all addreses) ballance in satoshi
    QStringList getAddressList();                           //return addresses and balances string list
    void sendBtc(QString reciverAddr, double ammount);      //func to send btc
    QString getAddress(int index);                          //return address str at index


private:

    QVector <BtcAddress*> addrList;     //holds btc addresses
    double balance;                     //holds wallet (All addresses) balance
    HttpRequest httpRequest;            //request to update addrest list and balance
    HttpRequest txRequest;              //request to update tx list
    HttpRequest sendBtcRequest;         //request for sending btc's
    QJsonDocument jSonDocument;         //holds JSON reply from httpRequest
    QString walletId;                   //holds wallet id from constructor
    QString pass;                       // holds pass from constructor
    QSystemTrayIcon newTxNotify;        //to show notify with new transaction
    void updateBalance(double txVal);   //update ballance
    void setAddressList(QJsonDocument* doc);  //save btcaddress in btcaddr list
    void getTx();

private slots:
    void notify(QString btcAddress, double balance, double oldBalance);     //shows notify for new tx
    void saveHttpReply(QByteArray data);                                    //save reply from address requests
    void saveTxList(QByteArray data);                                       //save reply from txs request

public slots:
    void update();                                                //update all addreses in address list


signals:
    void listUpdate(QStringList, double);      //signal to update addrlist and balance
    void txListReady(QByteArray);              //signal when tx list is ready to read
};

#endif // WALLET_H
