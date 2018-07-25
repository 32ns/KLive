#include "linju.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

LinJu::LinJu(QObject *parent) : Platfrom(parent)
{
    m_Http = new HttpManager(this);
    connect(m_Http,&HttpManager::sig_ReadFinish,this,&LinJu::readFinish);
}

LinJu::~LinJu()
{
    if(m_Http) delete m_Http;
}


/******************************************************************
    读取数据完成
******************************************************************/
void LinJu::readFinish(QByteArray data, READCMD cmd)
{
    switch (cmd) {

    case READCMD::GetRoomList:{
        this->getRoomListFinish(data);
    }break;

    case READCMD::GetRoomItem:{
        this->getRoomItemFinish(data);
    }break;


    default: qDebug()<<data;
        break;
    }
}


/******************************************************************
    获取房间列表
******************************************************************/
void LinJu::getRoomList()
{
    m_Http->get(QUrl("http://api.hclyz.cn:81/mf/json.txt"),READCMD::GetRoomList);
}


/******************************************************************
    获取房间列表完成
******************************************************************/
void LinJu::getRoomListFinish(QByteArray data)
{
    QList<PlatfromInfo> infolist;

    QJsonObject json = QJsonDocument::fromJson(data).object();
    QJsonArray ja = json.value("pingtai").toArray();
    for(int i=0; i<ja.count(); i++)
    {
        QJsonObject roomjson = ja.at(i).toObject();
        PlatfromInfo info;
        info.name = roomjson.value("title").toString();
        info.logo = roomjson.value("xinimg").toString();
        info.address = roomjson.value("address").toString();
        info.number = roomjson.value("Number").toString();
        infolist.append(info);
    }

    emit sig_GetRoomFinish(infolist);
}


/******************************************************************
    获取房间列表项
******************************************************************/
void LinJu::getRoomItem(QString address)
{
    if(address.isEmpty())
    {
        return;
    }

    QString url("http://api.hclyz.cn:81/mf/");
    url.append(address);

    m_Http->get(QUrl(url),READCMD::GetRoomItem);
}


/******************************************************************
    返回房间列表项完成
******************************************************************/
void LinJu::getRoomItemFinish(QByteArray data)
{
    QList<PlatfromItem> itemlist;

    QJsonObject json = QJsonDocument::fromJson(data).object();
    QJsonArray ja = json.value("zhubo").toArray();

    for(int i=0;i<ja.count();i++)
    {
        PlatfromItem item;
        QJsonObject itemjson = ja.at(i).toObject();
        item.name = itemjson.value("title").toString();
        item.logo = itemjson.value("img").toString();
        item.url = itemjson.value("address").toString();
        itemlist.append(item);
    }

    emit sig_GetRoomItemFinish(itemlist);
}





















