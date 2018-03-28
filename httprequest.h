#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest();
    void send();
    void setUrl(QString urlStr);



private:
    QNetworkAccessManager* nManager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl url;
    void httpError(QNetworkReply* reply);




private slots:
    void readReady(QNetworkReply* reply);


signals:
    void dataReadReady(QByteArray);

};

#endif // HTTPREQUEST_H
