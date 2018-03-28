#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
{


}

MainWindow::MainWindow(QWidget* parent, QString id, QString walletPass) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    walletID = id;
    pass = walletPass;
    qDebug() << walletID << pass;
}

MainWindow::~MainWindow()
{
    delete ui;
}


