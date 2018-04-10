#ifndef TXMODEL_H
#define TXMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

class TxModel : public QStandardItemModel
{
public:
    TxModel();
    void load(QByteArray dataArray);            //load byte array to parase json

};

#endif // TXMODEL_H
