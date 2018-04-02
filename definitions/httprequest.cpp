#include "../headers/httprequest.h"

HttpRequest::HttpRequest()
{
    nManager = new QNetworkAccessManager;
    connect(nManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readReady(QNetworkReply*)));
    connect(this, SIGNAL(dataReadReady(QByteArray)), this, SLOT(setDataStr(QByteArray)));

}

void HttpRequest::send()
{
    if (request.url().toString(QUrl::None).contains("https", Qt::CaseInsensitive))
    {

        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
        nManager->get(request);

    }
    else
        nManager->get(request);

}

void HttpRequest::setUrl(QString urlStr)
{
    url = QUrl(urlStr);
    request.setUrl(url);
}

void HttpRequest::httpError(QNetworkReply* reply) const
{

    QMessageBox::warning(NULL, "Error", reply->errorString(), QMessageBox::Ok);
}

QString HttpRequest::getDataStr() const
{

    return dataStr;
}

QByteArray HttpRequest::getDataByteArray() const
{

    return dataArray;
}

QUrl HttpRequest::getUrl() const
{
    return url;
}


void HttpRequest::readReady(QNetworkReply* reply)
{
    if (reply->error())
        httpError(reply);
    else
    {

        dataArray = reply->readAll();
        setDataStr(dataArray);
        emit(dataReadReady(dataArray));

    }
}

void HttpRequest::setDataStr(QByteArray data)
{
    dataStr = QString::fromStdString(data.toStdString());
    dataArray = data;
}







