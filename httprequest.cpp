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

void HttpRequest::httpError(QNetworkReply *reply)
{

    QMessageBox::warning(NULL,"Error",reply->errorString(),QMessageBox::Ok);
}


void HttpRequest::readReady(QNetworkReply *reply)
{
    if(reply->error()) httpError(reply);
    else
    {
    QByteArray myData;
    myData = reply->readAll();
    emit(dataReadReady(myData));
    }
}







