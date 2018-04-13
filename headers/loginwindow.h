#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#define CHECK_LOGIN_URL "https://35.196.109.84:3000/merchant/"+walletID+"/balance?password="+pass

#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QFile>

#include "httprequest.h"
#include "mainwindow.h"

const int MIN_SIGNS = 4;           //minimum signs amount in login and pass fields


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget* parent = 0);
    ~LoginWindow();

private:
    QTimer* timer;
    Ui::LoginWindow* ui;
    HttpRequest httpRequest;
    QFile loginFile;
    QString walletID;
    QString pass;

    void rememberPass();                        //func to save login and pass in file
    void loadLogin();                           //func to load login and pass from file
    QString encrypt(QString data);              //func to encrypt login and pass
    QString decrypt(QString data);              //func to decrypt login and pass


private slots:
    void updateTime();                          //slot to updating clock
    void enableLoginButton();                   //slot to enable login button
    void doLogin();                             //slot for logging
    void on_settingsButton_clicked();
    void checkLogin();                          //check if login and pass is valid
};

#endif // LOGINWINDOW_H
