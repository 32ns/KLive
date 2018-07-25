#include "httpmanager.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>

HttpManager::HttpManager(QObject *parent) : QObject(parent)
{
    m_NetManger = new QNetworkAccessManager(this);
    connect(m_NetManger,&QNetworkAccessManager::finished,this,&HttpManager::finished);
}

HttpManager::~HttpManager()
{
    if(m_NetManger) delete m_NetManger;
}


/******************************************************************
    get   url请求地址  cmd当前是什么请求
******************************************************************/
void HttpManager::get(QUrl url, READCMD cmd)
{
    this->currentCmd = cmd;

    QNetworkRequest m_request;
    m_request.setUrl(url);
    m_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    m_NetManger->get(m_request);
}


/******************************************************************
    post        url请求地址 data要发送的数据  cmd当前是什么请求
******************************************************************/
void HttpManager::post(QUrl url, QByteArray data, READCMD cmd)
{
    this->currentCmd = cmd;

    QNetworkRequest m_request;
    m_request.setUrl(url);
    m_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QStringList ua = appConfig.ua.split(":");
    if(ua.count()>1)
    {
        m_request.setRawHeader(ua[0].toUtf8(),ua[1].toUtf8());
    }

    m_NetManger->post(m_request,data);
}


/******************************************************************
    数据返回
******************************************************************/
void HttpManager::finished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    switch (this->currentCmd) {

    case READCMD::Init : {
        emit sig_ReadFinish(data,currentCmd);
    }break;

    case READCMD::GetRoomList : {       
        emit sig_ReadFinish(data,currentCmd);
    }break;

    case READCMD::GetRoomItem : {
        emit sig_ReadFinish(data,currentCmd);
    }break;


    case READCMD::UserLogin : {
        emit sig_ReadFinish(data,currentCmd);
    }break;

    case READCMD::UserReg : {
        emit sig_ReadFinish(data,currentCmd);
    }break;

    default:
        break;
    }

}



/******************************************************************
    获取时间戳
******************************************************************/
QString HttpManager::getTimeStamp(QDateTime time)
{
    uint timeT = time.toTime_t();   //将当前时间转为时间戳
    return QString::number(timeT);
}









