#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>

#include "httprequest.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private:
    QTimer *timer;
    Ui::LoginWindow *ui;
    HttpRequest httpRequest;





private slots:
    void updateTime();
    void enableLoginButton();
    void doLogin();
    void collectedData(QByteArray data_);
};

#endif // LOGINWINDOW_H
