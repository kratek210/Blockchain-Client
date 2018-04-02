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

    if (arr.size() != addrList.size() && !addrList.isEmpty())
    {

        for (int i = 0; i < addrList.size() + 1; i++)
        {
            QJsonObject obj = arr.at(i).toObject();

            if (addrList.last()->getAddress() != obj.value("receiveAddress").toString())
            {
                for (int j = addrList.size() - 1; j > -1; j--)
                {
                    delete addrList.last();
                    addrList.removeLast();
                }
            }
        }
        for (int k = 0; k < arr.size(); k++)
        {
            QJsonObject obj = arr.at(k).toObject();
            addrList << new BtcAddress(obj.value("receiveAddress").toString());
            addrList.at(k)->setAddrLabel(obj.value("label").toString());

            qDebug() << addrList.at(k)->getAddrLabel() << addrList.at(k)->getAddress() << addrList.at(k)->getBalance();
            qDebug() << addrList.size() << "from not empty or changed";
        }
    }

    if (addrList.isEmpty())
    {
        for (int i = 0; i < arr.size(); i++)
        {
            QJsonObject obj = arr.at(i).toObject();
            addrList << new BtcAddress(obj.value("receiveAddress").toString());
            addrList.at(i)->setAddrLabel(obj.value("label").toString());
            qDebug() << addrList.at(i)->getAddrLabel() << addrList.at(i)->getAddress() << addrList.at(i)->getBalance();
            qDebug() << addrList.size() << "from empty";

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
