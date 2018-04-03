#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent, QString id, QString walletPass) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    wallet = new Wallet(this, id, walletPass);
    timer.start(REFRESHING_PERIOD);
    updateBalanceLabel();
    connect(&timer, SIGNAL(timeout()), wallet, SLOT(update()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateBalanceLabel()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBalanceLabel()
{
    ui->balanceLabel->setText(QString::number(wallet->getBalance() / SATOSHI_TO_BTC_RATIO, 'f', 8).toUpper() + " BTC");
}



