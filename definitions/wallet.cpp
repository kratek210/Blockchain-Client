#include "../headers/wallet.h"


Wallet::Wallet(QObject* parent, QString login, QString password) : QObject(parent)
{
    connect(&httpRequest, SIGNAL(dataReadReady(QByteArray)), this, SLOT(saveHttpReply(QByteArray)));
    connect(&txRequest, SIGNAL(dataReadReady(QByteArray)), this, SLOT(saveTxList(QByteArray)));

    balance = 0;       //to avoid some crazy numbers from memory
    walletId = login;
    pass = password;
    httpRequest.setUrl(CHECK_WALLET);
    httpRequest.send();
    newTxNotify.setContextMenu(NULL);
    getTx();




}

double Wallet::getBalance()
{

    return balance;

}


void Wallet::getTx()
{
    QString addresses;
    for (int i = 0; i < addrList.size(); i++)
    {
        addresses += addrList.at(i)->getAddress() + "|";
    }
    txRequest.setUrl(TX_LIST_URL);// + addresses);
    txRequest.send();


}


QStringList Wallet::getAddressList()
{
    QStringList strList;
    strList.clear();
    if (!addrList.isEmpty())
    {
        for (int i = 0; i < addrList.size(); i++)
        {
            strList << addrList.at(i)->getAddrLabel() + "  " + addrList.at(i)->getAddress()
                    + " " + QString::number(addrList.at(i)->getBalance() / SATOSHI_TO_BTC_RATIO, 'f', 6) + " BTC";
        }

    }
    return strList;
}

void Wallet::sendBtc(QString reciverAddr, double ammount)
{

    sendBtcRequest.setUrl(SEND_BTC_URL + QString::number(ammount * SATOSHI_TO_BTC_RATIO));
    sendBtcRequest.send();
    qDebug() << sendBtcRequest.getUrl().toString();
}


void Wallet::update()
{
    if (httpRequest.getUrl() != QUrl(CHECK_WALLET).toString())
        httpRequest.setUrl(CHECK_WALLET);
    httpRequest.send();
    if (!addrList.isEmpty())
    {
        for (int i = 0; i < addrList.size() - 1; i++)
        {
            addrList.at(i)->update();
        }
    }
    getTx();
}

void Wallet::updateBalance(double txVal)
{
    if (txVal < 0)
        balance -= txVal;
    else
        balance += txVal;
}

void Wallet::setAddressList(QJsonDocument* doc)
{
    QJsonArray arr;
    arr = doc->array();
    if (addrList.isEmpty())
    {
        QJsonObject obj;
        for (int i = 0; i < arr.size(); i++)
        {
            obj = arr.at(i).toObject();
            addrList << new BtcAddress(obj.value("receiveAddress").toString());
            addrList.at(i)->setAddrLabel(obj.value("label").toString());

        }
    }
    else
    {
        QJsonObject obj;
        QStringList replyAdrList;
        QStringList localAddrList;

        for (int i = 0; i < arr.size(); i++)
        {
            obj = arr.at(i).toObject();
            replyAdrList << obj.value("receiveAddress").toString();
        }
        for (int i = 0; i < addrList.size(); i++)
        {
            localAddrList << addrList.at(i)->getAddress();
        }
        if (replyAdrList != localAddrList)
            addrList.clear();
        else {
            emit listUpdate(getAddressList(), balance);
        }





    }


}


void Wallet::notify(QString btcAddress, double balance, double oldBalance)
{
    double diffrence = balance - oldBalance;
    updateBalance(diffrence);
    newTxNotify.show();
    newTxNotify.showMessage(tr("New Transaction"), tr("New transaction on address: ") +
                            btcAddress + tr(" ammount: ") +
                            QString::number(diffrence, 'f', 8), QSystemTrayIcon::Information, 5000);
    newTxNotify.hide();

}

void Wallet::saveHttpReply(QByteArray data)
{
    QJsonParseError err;
    jSonDocument = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
        QMessageBox::warning(NULL, tr("JSON Error"),
                             err.errorString(), QMessageBox::Ok);
    else
        setAddressList(&jSonDocument);

}

void Wallet::saveTxList(QByteArray data)
{

    emit txListReady(data);


}
