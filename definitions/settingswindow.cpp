#include "../headers/settingswindow.h"
#include "ui_settingswindow.h"
settingsWindow::settingsWindow(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::settingsWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Settings"));
    setWindowModality(Qt::WindowModal);

    QSettings* settings = new QSettings("kratek", "blockchain", this);
    setHost(settings->value("HOST").toString());
    setPort(settings->value("PORT").toInt());
    setRefresh(settings->value("REFRESH").toInt());
    setMaxTx(settings->value("MAX_TX_LIMIT").toInt());
}

settingsWindow::~settingsWindow()
{
    delete ui;
}

void settingsWindow::setHost(QString host)
{
    ui->hostEdit->setText(host);
}

void settingsWindow::setPort(int port)
{
    ui->portBox->setValue(port);
}

void settingsWindow::setRefresh(int refresh)
{
    ui->refreshBox->setValue(refresh);
}

void settingsWindow::setMaxTx(int maxTxs)
{
    ui->txBox->setValue(maxTxs);
}

void settingsWindow::on_okButton_clicked()
{

    QSettings* settings = new QSettings("kratek", "blockchain", this);
    settings->setValue("HOST", ui->hostEdit->text());
    settings->setValue("PORT", ui->portBox->value());
    settings->setValue("REFRESH", ui->refreshBox->value());
    settings->setValue("MAX_TX_LIMIT", ui->txBox->value());
    close();
}

void settingsWindow::on_cancelButton_clicked()
{
    close();
}
