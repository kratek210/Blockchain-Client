#include "../headers/wallet.h"


Wallet::Wallet(QObject* parent, QString login, QString password) : QObject(parent)
{
    connect(&httpRequest, SIGNAL(dataReadReady(QByteArray)), this, SLOT(saveHttpReply(QByteArray)));

    balance = 0;       //to avoid some crazy numbers from memory
    walletId = login;
    pass = password;
    httpRequest.setUrl(CHECK_WALLET);
    httpRequest.send();

}

double Wallet::getBalance()
{
    return balance;
}


void Wallet::update()
{
    httpRequest.send();
    if (!addrList.isEmpty())
    {
        for (int i = 0; i < addrList.size() - 1; i++)
        {
            addrList.at(i)->update();
        }
    }
}

void Wallet::updateBalance(double txVal)
{
    if (txVal < 0)
        balance -= txVal;
    else
        balance += txVal;
}

void Wallet::getAddressList(QJsonDocument doc)
{
    QJsonArray arr;
    arr = doc.array();

    if (arr.size() != addrList.size() || addrList.isEmpty())
    {
        addrList.clear();
        for (int i = 0; i < arr.size() - 1; i++)
        {
            QJsonObject obj = arr.at(i).toObject();
            addrList << new BtcAddress(obj.value("receiveAddress").toString());
            addrList.at(i)->setAddrLabel(obj.value("label").toString());
            qDebug() << addrList.at(i)->getAddrLabel() << addrList.at(i)->getAddress() << addrList.at(i)->getBalance();
            qDebug() << addrList.size();
        }
    }
    else
    {
        for (int i = 0; i < addrList.size() - 1; i++)    //check is address under index is difrent from reply
        {
            QJsonObject obj = arr.at(i).toObject();
            if (obj.value("receiveAddress").toString() != addrList.at(i)->getAddress())
                addrList.clear();
        }
    }
}


void Wallet::notify(QString btcAddress, double balance, double oldBalance)
{
    double diffrence = balance - oldBalance;
    updateBalance(diffrence);

}

void Wallet::saveHttpReply(QByteArray data)
{
    QJsonParseError err;
    jSonDocument = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
        QMessageBox::warning(NULL, tr("JSON Error"),
                             err.errorString(), QMessageBox::Ok);
    else
        getAddressList(jSonDocument);
}
