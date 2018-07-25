#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket = new QWebSocket();
    connect(socket,&QWebSocket::connected,this,&Widget::connected);
    connect(socket,&QWebSocket::disconnected,this,&Widget::disconnected);
    connect(socket,&QWebSocket::binaryMessageReceived,this,&Widget::binaryMessageReceived);

    connTimer = new QTimer();
    connect(connTimer,&QTimer::timeout,this,&Widget::connectServer);

    connTimer->start(2000);
}

Widget::~Widget()
{
    delete ui;
}


/******************************************************************
    连接服务器
******************************************************************/
void Widget::connectServer()
{
    socket->open(QUrl("ws://kanlive.tk:1650"));
}

void Widget::connected()
{
    connTimer->stop();
    qDebug()<<"连接服务器成功";
}

void Widget::disconnected()
{
    ui->label->clear();
    qDebug()<<"与服务器断开连接";
    connTimer->start(2000);
}


/******************************************************************
    接收消息
******************************************************************/
void Widget::binaryMessageReceived(const QByteArray &message)
{
    QPixmap pix;
    pix.loadFromData(message);
    ui->label->setPixmap(pix);
}
