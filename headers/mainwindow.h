#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define CHECK_BALANCE_URL "http://127.0.0.1:3000/merchant/"+walletID+"/balance?password="+pass

#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include "headers/httprequest.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    explicit MainWindow(QWidget* parent, QString id, QString walletPass);
    ~MainWindow();


private:
    const double SATOSHI_TO_BTC = 100000000;
    Ui::MainWindow* ui;
    QString pass;
    QString walletID;
    QTimer timer;           //to update data
    HttpRequest request;
    HttpRequest updateBalanceRequest;
    QString dataStr;        //holds http request data as String
    QByteArray dataArray;   //holds http request data as ByteArray
    QJsonDocument jSonData; //holds Json response



private slots:

    void saveReqData(QByteArray data_);
    void updateBalance();
    void handleParasingError(QString errMsg);
signals:
    void jsonParasingError(QString);
};

#endif // MAINWINDOW_H
