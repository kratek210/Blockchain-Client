#ifndef BTCADDRES_H
#define BTCADDRES_H

#define CHECK_ADDRESS_BALANCE_URL "https://blockchain.info/q/addressbalance/"+addr

#include <QObject>
#include "httprequest.h"



class BtcAddress : public QObject
{
    Q_OBJECT
public:

    BtcAddress(QString Btcaddres);
    ~BtcAddress();
    void update();                      //sending request to update balance
    void setAddrLabel(QString label);   //set addr label
    QString getAddress() const;         //return BTC address
    double getBalance() const;          //return acctual balance
    QString getAddrLabel() const;       //return addr label


private:
    QString addr;                       //holds BTC address
    QString addrLabel;                  //holds addr label
    double balance;                     //hold address balance
    double tempBalance;                 //to hold old balance for compare
    HttpRequest* request;                //request for check addr balance


private slots:
    void saveHttpReply(QByteArray data);       //compare balance with reply and emit signal if diffrent


signals:
    void balanceChanged(QString, double, double);   //emited when balance change

};

#endif // BTCADDRES_H
