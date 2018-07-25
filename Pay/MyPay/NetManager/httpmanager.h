#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "cookiejar.h"

class HttpManager : public QObject
{
public:
    enum ReadCmd{
        getUUID,
        getQRCode,
        waitForLogin,
        getLoginInfo,
        userInit,
        statusNotifyFinish,
        syncStatus,
        syncMessage,
        exitLogin,
        sendMessage
    };

    Q_OBJECT
public:
    explicit HttpManager(QObject *parent = nullptr);
    ~HttpManager();

private:
    QNetworkAccessManager *network = NULL;
    CookieJar *mycookie=NULL;
    ReadCmd currentCmd;

signals:
    void sig_Finished(QByteArray data,ReadCmd cmd);

public slots:
    void get(QUrl url,ReadCmd cmd);
    void post(QUrl url,QByteArray data,ReadCmd cmd);
    void finished(QNetworkReply *reply);

};

#endif // HTTPMANAGER_H
