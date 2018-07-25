#include "websocket.h"

WebSocket::WebSocket(qint64 port,QObject *parent) : QObject(parent),
    m_server(new QWebSocketServer("klive",QWebSocketServer::NonSecureMode))
{
    if(m_server->listen(QHostAddress::Any,port))
    {
        connect(m_server,&QWebSocketServer::newConnection,this,&WebSocket::onNewConnection);
        connect(m_server,&QWebSocketServer::destroyed,this,&WebSocket::socketDisconnected);

        qDebug()<<"打开服务监听成功...";
    }else
    {
        qDebug()<<"打开服务器监听失败!";
    }
}

WebSocket::~WebSocket()
{   
    if(m_server)
    {
        m_server->close();
        delete m_server;
    }
    qDeleteAll(m_clients.begin(), m_clients.end());
}


/******************************************************************
    新连接到达
******************************************************************/
void WebSocket::onNewConnection()
{
    qDebug() << "new  connection";
    QWebSocket *pSocket = m_server->nextPendingConnection();
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocket::binaryMessageReceived);
    connect(pSocket, &QWebSocket::disconnected, this, &WebSocket::socketDisconnected);
    m_clients << pSocket;
    emit sig_newConnection();
}


/******************************************************************
    用户断开
******************************************************************/
void WebSocket::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket*>(sender());
    qDebug() << "socketDisconnected: " << pClient;

    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}


/******************************************************************
    接收数据
******************************************************************/
void WebSocket::binaryMessageReceived(const QByteArray &message)
{
    qDebug()<<message;
}


/******************************************************************
    发送信息
******************************************************************/
void WebSocket::sendMessage(QByteArray msg)
{
    for(int i=0;i<m_clients.count();i++)
    {
        m_clients.at(i)->sendBinaryMessage(msg);
        m_clients.at(i)->flush();
    }
}
