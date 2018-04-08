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
    ui->tableView->setColumnWidth(0, 110);
    ui->tableView->setColumnWidth(1, 160);
    ui->tableView->setColumnWidth(2, 400);
    //ui->tableView->setColumnWidth(3, 125);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);

    TxModel* model = new TxModel();
    model->load(array);
    ui->tableView->setModel(model);




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
