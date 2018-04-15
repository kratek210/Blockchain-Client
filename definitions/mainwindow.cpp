#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "../qrencode/qrencode.h"




MainWindow::MainWindow(QWidget* parent, QString id, QString walletPass) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings* settings = new QSettings("kratek", "blockchain", this);
    //setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    wallet = new Wallet(this, id, walletPass);

    if (settings->value("REFRESH").isNull())
        timer.start(REFRESHING_PERIOD);
    else
        timer.start(settings->value("REFRESH").toInt() * 1000);

    wallet->update();
    createTrayIcon();





    connect(&timer, SIGNAL(timeout()), wallet, SLOT(update()));
    connect(wallet, SIGNAL(listUpdate(QStringList, double)), this, SLOT(updateComboBal(QStringList, double)));
    connect(wallet, SIGNAL(txListReady(QByteArray)), this, SLOT(updateTx(QByteArray)));
    connect(ui->sendAddrEdit, SIGNAL(textChanged(QString)), this, SLOT(enableSendButton()));
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(enableSendButton()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(generateQrCode(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lastTransaction()
{
    QStringList tempList;
    if (!labelsTxs.isEmpty())
    {
        for (int i = 0; i < labelsTxs.size(); i++)
        {
            labelsTxs.at(i)->hide();
        }
        labelsTxs.clear();
    }
    if (model.rowCount() > LAST_TX_LIMIT)
    {   for (int i = 0; i < LAST_TX_LIMIT; i++)
        {
            if (model.item(i, 3)->text().toDouble() < 0)
                tempList += "<img src=:/res/red-down-arrow-hi.png style=float:left/>"
                            + model.item(i, 0)->text() + "<br><i>" + model.item(i, 2)->text()
                            + "</i> <font color=red><b>" + model.item(i, 3)->text() +
                            "</b></font>";
            else
                tempList += "<img src=:/res/arrowupgreen.png style=float:left/>"
                            + model.item(i, 0)->text() + "<br><i>"
                            + model.item(i, 2)->text()
                            + "</i> <font color=green><b>"
                            + model.item(i, 3)->text()
                            + "</b></font>";
        }
        for (int i = 0; i < tempList.size(); i++)
        {


            labelsTxs << new QLabel(tempList.at(i), ui->groupBox_2, Qt::Widget);
            ui->lastTxLayout->addWidget(labelsTxs[i]);
            labelsTxs.at(i)->show();
        }
    }
    else
    {
        {   for (int i = 0; i < model.rowCount(); i++)
            {
                if (model.item(i, 3)->text().toDouble() < 0)
                    tempList += "<img src=:/res/red-down-arrow-hi.png style=float:left/>"
                                + model.item(i, 0)->text() + "<br><i>" + model.item(i, 2)->text()
                                + "</i> <font color=red><b>" + model.item(i, 3)->text() +
                                "</b></font>";
                else
                    tempList += "<img src=:/res/arrowupgreen.png style=float:left/>"
                                + model.item(i, 0)->text() + "<br><i>"
                                + model.item(i, 2)->text()
                                + "</i> <font color=green><b>"
                                + model.item(i, 3)->text()
                                + "</b></font>";
            }
            for (int i = 0; i < tempList.size(); i++)
            {


                labelsTxs << new QLabel(tempList.at(i), ui->groupBox_2, Qt::Widget);
                ui->lastTxLayout->addWidget(labelsTxs[i]);
                labelsTxs.at(i)->show();
            }
        }
    }
}

void MainWindow::createTrayIcon()
{
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(QIcon(":/res/btcicon.png"), this);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showHide(QSystemTrayIcon::ActivationReason)));

    QAction* quitAction = new QAction("Exit", trayIcon);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    QAction* hideAction = new QAction("Show/Hide", trayIcon);
    connect(hideAction, SIGNAL(triggered()), this, SLOT(showHide()));

    QMenu* trayIconMenu = new QMenu;
    trayIconMenu->addAction(hideAction);
    trayIconMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayIconMenu);

    trayIcon->show();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    int reply;
    QMessageBox* msg = new QMessageBox(QMessageBox::Question, tr("Do you want to close?"), tr("Do you want to close or minimize to tray?"),
                                       QMessageBox::StandardButton::Apply |
                                       QMessageBox::StandardButton::Close | QMessageBox::StandardButton::Cancel, NULL);
    msg->setButtonText(QMessageBox::StandardButton::Apply, tr("Minimize to tray"));
    reply = msg->exec();
    if (reply == QMessageBox::StandardButton::Apply)
    {
        event->ignore();
        showHide();
    }
    if (reply == QMessageBox::StandardButton::Close)
    {
        event->accept();

    }
    if (reply == QMessageBox::StandardButton::Cancel)
    {
        event->ignore();
        show();
    }

}


void MainWindow::updateComboBal(QStringList AddrList, double wBalance)
{
    QStringList temp;
    for (int i = 0; i < ui->comboBox->count(); i++)
    {
        temp << ui->comboBox->itemText(i);
    }
    if (temp != AddrList)
    {
        ui->comboBox->clear();
        ui->comboBox->addItems(AddrList);
        ui->balanceLabel->setText(QString::number(wBalance / SATOSHI_TO_BTC_RATIO, 'f', 8).toUpper() + " BTC");
        ui->balanceLabel2->setText(QString::number(wBalance / SATOSHI_TO_BTC_RATIO, 'f', 8).toUpper() + " BTC");
    }

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
    model.load(array);
    ui->tableView->setModel(&model);
    lastTransaction();

}

void MainWindow::on_pushButton_clicked()
{
    QString addr;
    int index;
    index = ui->comboBox->currentIndex();
    addr = wallet->getAddress(index);
    QClipboard* temp = QApplication::clipboard();
    temp->setText(addr, QClipboard::Clipboard);

}

void MainWindow::enableSendButton()
{

    if (ui->doubleSpinBox->value() > 0 && ui->sendAddrEdit->text().count() > 25)
        ui->btcSendButton->setEnabled(true);
    else
        ui->btcSendButton->setEnabled(false);
}

void MainWindow::on_btcSendButton_clicked()
{
    wallet->sendBtc(ui->sendAddrEdit->text(), ui->doubleSpinBox->value());
}

void MainWindow::generateQrCode(int index)
{

    ui->codeLayout->addWidget(code);
    code->setMargin(3);
    code->setText("bitcoin:" + wallet->getAddress(index));
    code->show();
}

void MainWindow::showHide(QSystemTrayIcon::ActivationReason reason)
{
    if (reason)
    {
        if (reason != QSystemTrayIcon::DoubleClick)
            return;
    }

    if (isVisible())
    {
        hide();
    }
    else
    {
        show();
        raise();
        setFocus();
    }
}

void MainWindow::showHide()
{
    if (isVisible())
        hide();
    else
        show();
}
