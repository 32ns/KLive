#include "httpmanager.h"

#include <QEventLoop>

HttpManager::HttpManager(QObject *parent) : QObject(parent)
{
    mycookie = new CookieJar(this);

    network = new QNetworkAccessManager(this);
    network->setCookieJar(mycookie);

    connect(network,&QNetworkAccessManager::finished,this,&HttpManager::finished);
}

HttpManager::~HttpManager()
{
    if(network) delete network;
}


/******************************************************************
    get
******************************************************************/
void HttpManager::get(QUrl url,ReadCmd cmd)
{
    this->currentCmd = cmd;
    QNetworkRequest request;
    request.setUrl(url);

    network->get(request);
}



/******************************************************************
    post
******************************************************************/
void HttpManager::post(QUrl url, QByteArray data,ReadCmd cmd)
{
    this->currentCmd = cmd;
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=UTF-8");

    network->post(request,data);
}



/******************************************************************
    读取完成
******************************************************************/
void HttpManager::finished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    emit sig_Finished(data,currentCmd);
}


