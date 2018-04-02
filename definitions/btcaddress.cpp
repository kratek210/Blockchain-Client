#include "../headers/btcaddress.h"



BtcAddress::BtcAddress(QString Btcaddres)
{

    connect(&request, SIGNAL(dataReadReady(QByteArray)), this, SLOT(saveHttpReply(QByteArray)));

    addr = Btcaddres;
    request.setUrl(CHECK_ADDRESS_BALANCE_URL);
    request.send();
    tempBalance = 0;
    balance = 0;
}

QString BtcAddress::getAddress() const
{
    return addr;
}

double BtcAddress::getBalance() const
{
    return balance;
}

QString BtcAddress::getAddrLabel() const
{
    return addrLabel;
}

void BtcAddress::update()
{
    request.send();
}

void BtcAddress::setAddrLabel(QString label)
{
    addrLabel = label;
}

void BtcAddress::saveHttpReply(QByteArray data)
{
    tempBalance = balance;
    balance = data.toDouble();
    if (balance != data.toDouble())
        emit balanceChanged(addr, balance, tempBalance);
    balance = data.toDouble();


}
