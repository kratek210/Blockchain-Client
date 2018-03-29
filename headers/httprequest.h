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
    QString getDataStr() const;
    QByteArray getDataByteArray() const;
    QUrl getUrl() const;

private:
    QNetworkAccessManager* nManager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl url;
    QString dataStr;
    QByteArray dataArray;
    void httpError(QNetworkReply* reply) const;

private slots:
    void readReady(QNetworkReply* reply);
    void setDataStr(QByteArray data);




signals:
    void dataReadReady(QByteArray);
};

#endif // HTTPREQUEST_H
