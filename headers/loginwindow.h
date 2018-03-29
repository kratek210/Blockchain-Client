#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#define HOST "http://127.0.0.1:3000/merchant/"

#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QFile>

#include "httprequest.h"
#include "mainwindow.h"


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
    void rememberPass();
    void loadLogin();
    QString encrypt(QString data);
    QString decrypt(QString data);


private slots:
    void updateTime();
    void enableLoginButton();
    void doLogin();
    void on_settingsButton_clicked();
    void checkLogin();
};

#endif // LOGINWINDOW_H
