#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>

//读取的是什么
enum READCMD{
    Init,
    UserLogin,
    UserReg,
    GetConfigInfo,
    GetRoomList,
    GetRoomItem,
};

//应用配置
struct APPCONFIG{
    QString ua;     //浏览器 User-Agent
    QString user;   //用户
    QString livebroad;  //直播房间地址
    QString livekey;    //解码密钥

};

class Global
{

public:
    Global();
    static QString getDeviceid();
    static QByteArray getToken();


};

#endif // GLOBAL_H
