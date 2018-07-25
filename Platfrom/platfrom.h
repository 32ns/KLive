#ifndef PLATFROM_H
#define PLATFROM_H

#include <QObject>
#include "NetWork/httpmanager.h"

class Platfrom : public QObject
{
    Q_OBJECT
public:
    explicit Platfrom(QObject *parent = nullptr);
    ~Platfrom();

public:
    struct PlatfromInfo{
        QString name;       //平台名称
        QString logo;       //平台图片
        QString number;     //在线人数
        QString address;    //平台地址
    };
    struct PlatfromItem
    {
        QString name;       //主播昵称
        QString logo;       //主播头像
        QString url;        //播放地址
    };

signals:
    void sig_GetRoomFinish(QList<PlatfromInfo> infolist);
    void sig_GetRoomItemFinish(QList<PlatfromItem> itemlist);

public slots:
    virtual void getRoomList() = 0;
    virtual void getRoomItem(QString address) = 0;
};

#endif // PLATFROM_H
