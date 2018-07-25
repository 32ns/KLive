#ifndef LINJU_H
#define LINJU_H

/******************************************************************
    邻居家的耳朵
******************************************************************/

#include <QObject>
#include "platfrom.h"

class LinJu : public Platfrom
{
    Q_OBJECT
public:
    explicit LinJu(QObject *parent = nullptr);
    ~LinJu();

private:
    HttpManager *m_Http = NULL;

signals:

public slots:
    void readFinish(QByteArray data,READCMD cmd);   //读取数据完成

    void getRoomList();
    void getRoomListFinish(QByteArray data);

    void getRoomItem(QString address);
    void getRoomItemFinish(QByteArray data);
};

#endif // LINJU_H
