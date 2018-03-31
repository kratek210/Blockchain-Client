#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent, QString id, QString walletPass) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //SIGNALS AND SLOT CONNECTING
    for (int i = 0; i < OBJECTS_ARRAY_SIZE; i++)        //loop to connect every object from array to same slot
    {
        connect(&request[i], SIGNAL(dataReadReady(QByteArray)), this, SLOT(saveReqData(QByteArray)));
    }
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    /*--------------------------------------------------------------------------------------------*/

    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    walletID = id;
    pass = walletPass;
    timer.start(REFRESHING_PERIOD);
    request[BALANCE].setUrl(CHECK_BALANCE_URL);
    request[BALANCE].send();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveReqData(QByteArray data_)
{
    int index = 0;
    for (int i = 0; i < OBJECTS_ARRAY_SIZE; i++)        //loop to check HttpRequest object index in array
    {
        if (sender() == &request[i])
            index = i;
    }
    dataStr[index] = QString::fromStdString(data_.toStdString());  // to save reply at same index as HttpRequest index
    dataArray[index] = data_;

    jSonData[index] = QJsonDocument::fromJson(dataArray[index]);

}

void MainWindow::update()
{
    updateBalance();
    recentTxs();
    getWalletAddresses();
}

void MainWindow::updateBalance()
{

    if (request[BALANCE].getUrl().toString() != CHECK_BALANCE_URL)
    {
        request[BALANCE].setUrl(CHECK_BALANCE_URL);
    }
    request[BALANCE].send();
    if (jSonData[BALANCE].isEmpty())
        qDebug() << "Json Document with Balance is empty";

    else
    {
        QJsonObject obj;
        obj = jSonData[BALANCE].object();
        ui->balanceLabel->setText(QString::number(double(obj.value("final_balance").toDouble() / SATOSHI_TO_BTC), 'f', 8).toUpper() + " BTC");
        btcBalance = double(obj.value("final_balance").toDouble() / SATOSHI_TO_BTC);
    }

}

void MainWindow::recentTxs()
{
    if (request[TXS].getUrl().toString() != CHECK_TX)
    {
        request[TXS].setUrl(CHECK_TX);
        request[TXS].send();
    }
    else
    {
        request[TXS].send();
        if (jSonData[TXS].isEmpty())
        {

            qDebug() << "txs json empty";

        }

        else
        {
            QJsonObject obj;

            QJsonArray txs_array;
            obj = jSonData[TXS].object();
            txs_array = obj.value("txs").toArray();
            if (txs_array.size() > LAST_TRANSACTION_LIMIT - 1)
            {
                for (int i = 0; i < LAST_TRANSACTION_LIMIT; i++)
                {

                    QJsonObject obj[LAST_TRANSACTION_LIMIT];
                    obj[i] = txs_array.at(i).toObject();

                }

            }

        }

    }
}

void MainWindow::getWalletAddresses()
{

    if (request[ADDR].getUrl().toString() != LIST_WALLET_ADRESSES)
    {
        request[ADDR].setUrl(LIST_WALLET_ADRESSES);
        request[ADDR].send();
    }
    else
    {
        request[ADDR].send();

        if (jSonData[ADDR].isEmpty())
            qDebug() << "wallet adresses json empty";

        else
        {
            QJsonArray arr;
            arr = jSonData[ADDR].array();
            QJsonObject obj[arr.size()];


            if (btcAdresses.length() != arr.size())
            {
                btcAdresses.clear();
                for (int i = 0; i < arr.size(); i++)
                {


                    obj[i] = arr.at(i).toObject();
                    btcAdresses << obj[i].value("label").toString() + " " + obj[i].value("receiveAddress").toString();
                    //qDebug() << btcAdresses[i] << btcAdresses.size();

                }

            }

        }

    }
}



