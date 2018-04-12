

#include "../headers/loginwindow.h"
#include "ui_loginwindow.h"


LoginWindow::LoginWindow(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    timer = new QTimer(this);
    timer->start(1000);         //to update clock every 1000ms
    ui->setupUi(this);
    ui->loginButton->setDisabled(true); //disable login button

    /*SIGNALS AND SLOTS CONNECTING*/
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime())); //updating clock
    connect(ui->refreshButton, SIGNAL(clicked(bool)), ui->walletEdit, SLOT(clear())); //clear login form
    connect(ui->refreshButton, SIGNAL(clicked(bool)), ui->passEdit, SLOT(clear())); // clear pass form
    connect(ui->shutdownButton, SIGNAL(clicked(bool)), this, SLOT(close())); //close login window
    connect(ui->walletEdit, SIGNAL(textChanged(QString)), this, SLOT(enableLoginButton())); //enable login button
    connect(ui->passEdit, SIGNAL(textChanged(QString)), this, SLOT(enableLoginButton())); //enable login button
    connect(ui->loginButton, SIGNAL(clicked(bool)), this, SLOT(doLogin()));
    connect(&httpRequest, SIGNAL(dataReadReady(QByteArray)), this, SLOT(checkLogin()));
    /*-----------------------------------------------------------------------------------------*/

    loadLogin();
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
    if (ui->walletEdit->text().count() > MIN_SIGNS && ui->passEdit->text().count() > MIN_SIGNS) //check if forms have more than 4 letters
        ui->loginButton->setEnabled(true); //enable button
    else
        ui->loginButton->setEnabled(false); // else disable button
}

void LoginWindow::doLogin()
{
    walletID = ui->walletEdit->text();
    pass = ui->passEdit->text();
    httpRequest.setUrl(CHECK_LOGIN_URL);
    httpRequest.send();
    ui->loginButton->setEnabled(false);
    enableLoginButton();

}


void LoginWindow::checkLogin()
{

    if (httpRequest.getDataStr().contains("balance", Qt::CaseInsensitive))
    {

        rememberPass();
        MainWindow* mainWindow = new MainWindow(NULL, walletID, pass);

        mainWindow->show();

        this->close();


    }


    ui->loginButton->setEnabled(true);


}

void LoginWindow::rememberPass()
{
    if (ui->passCheckBox->isChecked())
    {
        loginFile.setFileName("data.dat");
        if (!loginFile.open(QIODevice::ReadWrite))
        {
            QMessageBox::warning(NULL, tr("Error"), loginFile.errorString(), QMessageBox::Ok);
        }

        else
        {
            QTextStream out(&loginFile);
            out << encrypt(walletID) << "\n" << encrypt(pass);
            loginFile.flush();
            loginFile.close();

        }

    }

}

void LoginWindow::loadLogin()
{
    loginFile.setFileName("data.dat");
    if (loginFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&loginFile);

        ui->walletEdit->setText(decrypt(in.readLine()));
        ui->passEdit->setText(decrypt(in.readLine()));

    }
}

QString LoginWindow::encrypt(QString data)  //very shitty encryption. better than plain text :)
{
    std::string pass = data.toStdString();
    QByteArray buf;

    for (int i = 0; i < int(pass.size()); i++)
    {
        pass[i] = pass[i] - 10;
        buf.append(pass[i]);
    }
    return QString::fromStdString(buf.toBase64().toStdString());

}

QString LoginWindow::decrypt(QString data)
{
    std::string pass;
    QByteArray buf;
    buf.append(data);
    pass = buf.fromBase64(buf).toStdString();


    for (int i = 0; i < int(pass.size()); i++)
    {
        pass[i] = pass[i] + 10;

    }
    return QString::fromStdString(pass);

}


void LoginWindow::on_settingsButton_clicked()
{
    QMessageBox::information(NULL, tr("Information"), tr("Not implemented yet. "
                                                         "Here will be posible "
                                                         "to change port number "
                                                         "of local service if user "
                                                         "starts Blockchain Api server on diffrent "
                                                         "port. Refreshing period. unit mBTC BTC etc."), QMessageBox::Ok);
}

