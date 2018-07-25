#include "download.h"

Download::Download(QObject *parent) : QObject(parent)
{        
    NetManager = new QNetworkAccessManager(this);
}

Download::~Download()
{
    if(File)delete File;
    if(Reply) delete Reply;
    if(NetManager) delete NetManager;
}


/******************************************************************
    用get获取数据
******************************************************************/
bool Download::startDown(QUrl url)
{
    if(url.isEmpty())
    {
        return false;
    }
    if(!File)
    {
        File = new QFile(url.fileName());
    }
    if(!File->open(QIODevice::WriteOnly))
    {
        File->flush();
        File->close();
        return false;
    }    
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    Reply = NetManager->get(request);
    connect(Reply,&QNetworkReply::finished,this,&Download::finished);
    connect(Reply,&QNetworkReply::readyRead,this,&Download::readyRead);
    connect(Reply,&QNetworkReply::downloadProgress,this,&Download::downloadProgress);
    return true;
}


/******************************************************************
    接收文件
******************************************************************/
void Download::readyRead()
{
    File->write(Reply->readAll());
}


/******************************************************************
    下载进度
******************************************************************/
void Download::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    int statusCode = Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    //QString strUrl = Reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
    if(statusCode == 0)
    {
        return;
    }
    //qDebug()<<"下载中: "<<(bytesReceived * 100 / bytesTotal)<<"%";
    emit sig_downloadProgress(bytesReceived,bytesTotal);
}



/******************************************************************
    下载完成
******************************************************************/
void Download::finished()
{    
    emit sig_DownLoadFinish(File->fileName());

    Reply->close();
    delete Reply;
    Reply = NULL;
    File->close();
    delete File;
    File = NULL;
}



