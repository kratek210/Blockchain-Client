#ifndef WALLET_H
#define WALLET_H

#define CHECK_WALLET "http://127.0.0.1:3000/merchant/"+walletId+"/accounts?password="+pass

#include "httprequest.h"
#include <QJsonObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include "btcaddress.h"

class Wallet : public QObject
{
    Q_OBJECT


public:
    explicit Wallet(QObject* parent, QString login, QString password);

    double getBalance();                //returns wallet (from all addreses) ballance in satoshi

private:
    double balance;                     //holds wallet (All addresses) balance
    HttpRequest httpRequest;            //request to update addrest list and balance
    QJsonDocument jSonDocument;         //holds JSON reply from httpRequest
    QString walletId;
    QString pass;
    QList <BtcAddress*> addrList;       //holds btc addresses
    void updateBalance(double txVal);   //update ballance
    void getAddressList(QJsonDocument doc);  //save btcaddress in btcaddr list


private slots:
    void notify(QString btcAddress, double balance, double oldBalance);
    void saveHttpReply(QByteArray data);

public slots:
    void update();                      //update all addreses in address list



};

#endif // WALLET_H
