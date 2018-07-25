#ifndef WECHAT_H
#define WECHAT_H

#include <QJsonObject>
#include <QObject>
#include <QTimer>
#include "NetManager/httpmanager.h"
#include "userpay.h"

class WeChat : public QObject
{
    Q_OBJECT
public:
    explicit WeChat(QObject *parent = nullptr);
    ~WeChat();

private:
    HttpManager *m_http = NULL;
    QString current_UUID;
    QHash<QString,QString>m_loginInfo;
    QString m_currentHost;
    QJsonObject m_SyncKey;
    QJsonObject m_UserInfo;
    QJsonObject m_BaseRequest;
    QString m_SyncHost;
    QStringList m_SyncHostList;
    int currentHostListjs = 0;

    QTimer *syncTimer = NULL;
    QTimer *msgToMe = NULL;

    UserPay *m_Pay = NULL;

signals:
    void sig_QRcodeArrive(QByteArray img);

public slots:
    void start();


private:
    QString getDeviceID();
    QString getTimeID();
    void getUUID();
    void getUUIDFinish(QByteArray data);

    void getQRCode(QString uuid);

    void waitForLogin(QString uuid);
    void waitForLoginFinish(QByteArray data);

    void getLoginInfo(QString url);
    void getLoginInfoFinish(QByteArray data);

    void userInit();
    void userInitFinish(QByteArray data);

    void statusNotify();
    void statusNotifyFinish(QByteArray data);

    void syncStatus();
    void syncStatusFinish(QByteArray data);

    void syncMesasge();
    void syncMesasgeFinish(QByteArray data);

    void sendMessage(QString ToUserName,QString msg);
    void sendMessageFinish(QByteArray data);

    void sendMessageToMe();

    void ReadFinished(QByteArray data,HttpManager::ReadCmd cmd);

    void exitLogin();
};

#endif // WECHAT_H
