#include "pay.h"
#include <QFile>

Pay::Pay(QObject *parent) : QObject(parent)
{
    m_socket = new WebSocket(1650,this);

    m_weixin = new WeChat(this);
    connect(m_weixin,&WeChat::sig_QRcodeArrive,this,&Pay::qRcodeArrive);    
    connect(m_socket,&WebSocket::sig_newConnection,this,&Pay::newConnection);
}

Pay::~Pay()
{
    if(m_socket) delete m_socket;
    if(m_weixin) delete m_weixin;    
}


/******************************************************************
    二唯码到达
******************************************************************/
void Pay::qRcodeArrive(QByteArray img)
{
    qDebug()<<"生成二唯码成功...";
    m_socket->sendMessage(img);
}


/******************************************************************
    有新连接到达
******************************************************************/
void Pay::newConnection()
{
    if(!isRun)
    {
        isRun = true;
        m_weixin->start();
    }
}
