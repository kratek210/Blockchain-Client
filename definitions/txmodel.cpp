#include "../headers/txmodel.h"
#include <QDebug>

TxModel::TxModel()
{
    setHorizontalHeaderLabels(QStringList() << "Date" << "Type" << "Address" << "Ammount");


}

void TxModel::load(QByteArray dataArray)
{
    QJsonDocument doc = QJsonDocument::fromJson(dataArray);
    QJsonObject obj = doc.object();
    QJsonArray arr = obj.value("txs").toArray();

    setRowCount(arr.size());
    for (int i = 0; i < arr.size(); i++)
    {
        QModelIndex  id = index(i, 0, QModelIndex());

        setData(id, QDateTime::fromSecsSinceEpoch(arr.at(i).toObject().value("time").toInt()), Qt::DisplayRole);
        item(i, 0)->setEditable(false);
        item(i, 0)->setTextAlignment(Qt::AlignCenter);
        id = index(i, 1, QModelIndex());

        if (arr.at(i).toObject().value("result").toDouble() > 0)
        {
            setData(id, "Recived", Qt::DisplayRole);
            item(i, 1)->setTextAlignment(Qt::AlignCenter);
            item(i, 1)->setEditable(false);
        }

        else
        {
            setData(id, "Sent", Qt::DisplayRole);
            item(i, 1)->setEditable(false);
            item(i, 1)->setTextAlignment(Qt::AlignCenter);

        }
        id = index(i, 2, QModelIndex());

        setData(id, arr.at(i).toObject().value("out").toArray().at(0).toObject().value("addr"), Qt::DisplayRole);
        item(i, 2)->setTextAlignment(Qt::AlignCenter);


        id = index(i, 3, QModelIndex());
        double btc = arr.at(i).toObject().value("result").toDouble() / 100000000;
        if (btc > 0)
        {
            setData(id, QString::number(btc, 'f', 8).toUpper(), Qt::DisplayRole);
            item(i, 3)->setForeground(Qt::green);
            item(i, 3)->setEditable(false);
            item(i, 3)->setTextAlignment(Qt::AlignCenter);


        }
        else
        {
            setData(id, QString::number(btc, 'f', 8).toUpper(), Qt::DisplayRole);
            item(i, 3)->setForeground(Qt::red);
            item(i, 3)->setEditable(false);
            item(i, 3)->setTextAlignment(Qt::AlignCenter);

        }


    }
}


