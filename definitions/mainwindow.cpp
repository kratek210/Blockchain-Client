#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow()
{


}

MainWindow::MainWindow(QWidget* parent, QString id, QString walletPass) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&request, SIGNAL(dataReadReady(QByteArray)), this, SLOT(saveReqData(QByteArray)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateBalance()));
    connect(this, SIGNAL(jsonParasingError(QString)), this, SLOT(handleParasingError(QString)));


    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    walletID = id;
    pass = walletPass;
    timer.start(1000);

}

MainWindow::~MainWindow()
{

    delete ui;

}

void MainWindow::saveReqData(QByteArray data_)
{

    dataStr = QString::fromStdString(data_.toStdString());
    dataArray = data_;

    jSonData = QJsonDocument::fromJson(dataArray);
    if (jSonData.isEmpty())
        emit jsonParasingError("JsonDocument is Empty");

}

void MainWindow::updateBalance()
{

    if (request.getUrl().toString() != CHECK_BALANCE_URL)
    {
        request.setUrl(CHECK_BALANCE_URL);
        request.send();
    }
    else
    {
        request.send();
        if (jSonData.isEmpty())
        {
            if (jSonData.isEmpty())
                QThread::msleep(500);   //wait until json parasing finish
        }

        else
        {
            QJsonObject obj;
            obj = jSonData.object();
            ui->balanceLabel->setText(QString::number(double(obj.value("final_balance").toDouble() / SATOSHI_TO_BTC), 'f', 8).toUpper() + " BTC");
        }





    }


}

void MainWindow::handleParasingError(QString errMsg)
{
    QMessageBox::warning(this, tr("Error"), tr("Error parasing JSON "
                                               "data. ") + errMsg
                         , QMessageBox::Ok);

}


