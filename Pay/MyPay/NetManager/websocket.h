#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QtWebSockets>

class WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WebSocket(qint64 port,QObject *parent = nullptr);
    ~WebSocket();

private:
    QWebSocketServer *m_server = NULL;
    QList<QWebSocket *> m_clients;

signals:
    void sig_newConnection();

public slots:
    void onNewConnection();
    void socketDisconnected();
    void binaryMessageReceived(const QByteArray &message);
    void sendMessage(QByteArray msg);
};

#endif // WEBSOCKET_H
