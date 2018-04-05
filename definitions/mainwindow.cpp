#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget* parent, QString id, QString walletPass) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    wallet = new Wallet(this, id, walletPass);
    timer.start(REFRESHING_PERIOD);
    wallet->update();


    connect(&timer, SIGNAL(timeout()), wallet, SLOT(update()));
    connect(wallet, SIGNAL(listUpdate(QStringList, double)), this, SLOT(updateComboBoxList(QStringList, double)));
    connect(wallet, SIGNAL(txListReady(QByteArray)), this, SLOT(updateTx(QByteArray)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateComboBoxList(QStringList AddrList, double wBalance)
{
    ui->comboBox->clear();
    ui->comboBox->addItems(AddrList);

    ui->balanceLabel->setText(QString::number(wBalance / SATOSHI_TO_BTC_RATIO, 'f', 8).toUpper() + " BTC");
    ui->balanceLabel2->setText(QString::number(wBalance / SATOSHI_TO_BTC_RATIO, 'f', 8).toUpper() + " BTC");

}

void MainWindow::updateTx(QByteArray array)
{
    QJsonModel* model = new QJsonModel;
    ui->treeView->setModel(model);

    model->loadJson(array);


}

void MainWindow::on_pushButton_clicked()
{
    QString addr;
    int index;
    index = ui->comboBox->currentIndex();
    addr = wallet->addrList.at(index)->getAddress();
    QClipboard* temp = QApplication::clipboard();
    temp->setText(addr, QClipboard::Clipboard);

}
