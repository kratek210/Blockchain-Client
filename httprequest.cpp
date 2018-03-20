#include "httprequest.h"

HttpRequest::HttpRequest()
{    
    connect(nManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(readReady(QNetworkReply*)));

}

void HttpRequest::send()
{
    nManager->get(request);
}

void HttpRequest::setUrl(QString urlStr)
{
    url=QUrl(urlStr);
    request.setUrl(url);
}



void HttpRequest::readReady(QNetworkReply *reply)
{
    QByteArray myData;
    myData = reply->readAll();
    emit(dataReadReady(myData));

}







