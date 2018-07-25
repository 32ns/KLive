#ifndef PAY_H
#define PAY_H

#include <QObject>
#include "wechat.h"
#include "NetManager/websocket.h"

class Pay : public QObject
{
    Q_OBJECT
public:
    explicit Pay(QObject *parent = nullptr);
    ~Pay();

private:
    WeChat *m_weixin = NULL;
    WebSocket *m_socket = NULL;
    bool isRun = false;

signals:

public slots:
    void qRcodeArrive(QByteArray img);
    void newConnection();
};

#endif // PAY_H
