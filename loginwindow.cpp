#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    timer = new QTimer(this);
    timer->start(1000);         //to update clock every 1000ms
    ui->setupUi(this);
    ui->loginButton->setDisabled(true); //disable login button


    /*SIGNALS AND SLOTS CONNECTING*/
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));   //updating clock
    connect(ui->refreshButton,SIGNAL(clicked(bool)),ui->walletEdit,SLOT(clear())); //clear login form
    connect(ui->refreshButton,SIGNAL(clicked(bool)),ui->passEdit,SLOT(clear()));  // clear pass form
    connect(ui->shutdownButton,SIGNAL(clicked(bool)),this,SLOT(close())); //close login window
    connect(ui->walletEdit,SIGNAL(textChanged(QString)),this,SLOT(enableLoginButton())); //enable login button
    connect(ui->passEdit,SIGNAL(textChanged(QString)),this,SLOT(enableLoginButton())); //enable login button

    connect(ui->loginButton,SIGNAL(clicked(bool)),this,SLOT(doLogin()));
    connect(&httpRequest,SIGNAL(dataReadReady(QByteArray)),this,SLOT(collectedData(QByteArray)));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::updateTime()
{
    ui->dateTime->setText(QDateTime::currentDateTime().toString("ddd d MMMM yyyy h:mm:ss"));
}

void LoginWindow::enableLoginButton()
{
    if(ui->walletEdit->text().count()>4 && ui->passEdit->text().count()>4) //check if forms have more than 4 letters
         ui->loginButton->setEnabled(true); //enable button
    else ui->loginButton->setEnabled(false); // else disable button
}

void LoginWindow::doLogin()
{
    httpRequest.setUrl("http://127.0.0.1:3000/merchant/"+ui->walletEdit->text()+"/balance?password="+ui->passEdit->text());
    httpRequest.send();

}

void LoginWindow::collectedData(QByteArray data_)
{

    dataStr = data_;



}

QString LoginWindow::returnHttpData()
{
    return dataStr;

}
