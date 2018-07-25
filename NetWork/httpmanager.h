#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include "Global/global.h"
#include <QNetworkAccessManager>

class HttpManager : public QObject
{
    Q_OBJECT
public:
    explicit HttpManager(QObject *parent = nullptr);
    ~HttpManager();
    APPCONFIG appConfig;    //App配置

private:
    QNetworkAccessManager *m_NetManger = NULL;
    READCMD currentCmd;


signals:
    void sig_ReadFinish(QByteArray data,READCMD cmd);   //读取数据完成


public slots:
    void get(QUrl url,READCMD cmd);
    void post(QUrl url,QByteArray data,READCMD cmd);
    QString getTimeStamp(QDateTime time);


private slots:
    void finished(QNetworkReply *reply);

};

#endif // HTTPMANAGER_H
