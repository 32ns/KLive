#ifndef LIVE_H
#define LIVE_H

#include <QObject>
#include "NetWork/httpmanager.h"
#include "Model/model_roomlist.h"
#include "Model/model_roomitem.h"
#include "Model/admodel.h"
#include <QSettings>
#include "NetWork/download.h"
#include "Platfrom/platfrom.h"

class Live : public QObject
{
    Q_OBJECT
public:
    explicit Live(QObject *parent = nullptr);
    ~Live();


public:
    Model_RoomList *roomModel = NULL;
    Model_RoomItem *roomItemModel = NULL;
    AdModel *model_ad = NULL;
    QString currentRoomName;

private:
    HttpManager *m_Http = NULL;
    QSettings *settings = NULL;
    Download *download = NULL;
    QString updateUrl = ""; //更新地址
    QString homeUrl = "http://127.0.0.1:8888/";
    QString qRcodePath;
    Platfrom *m_pingtai = NULL;


signals:
    void sig_UserState(int state,QString title);
    void sig_RoomItemCreateSucceed(QString roomname,int itemsum);
    void sig_Update(QString msg,QString url);
    void sig_downloadProgress(double all,double current);


private slots:
    void init();
    void serverMessage(QByteArray data);
    void readFinish(QByteArray data,READCMD cmd);   //拿到读取来的信息
    void updateMessage(QByteArray data);
    void installApp(QString filename);


public slots:
    void getUserState(QString roomname);    //返回用户状态

    void getRoomList();
    void getRoomFinish(QList<Platfrom::PlatfromInfo> infolist);

    void getRoomItem(QString roomname);
    void getRoomItemFinish(QList<Platfrom::PlatfromItem> itemlist);

    void loginUser(QString user, QString password);
    void regUser(QString user,QString password); //注册用户
    void userLoadSucceecd(QByteArray data);
    QString getPassCrypto(QString pass);
    QString getUserInfo_username();
    QString getUserInfo_endtimer();
    QString getTopUpUrl();
    void startUpdate();
    bool checkUserDate();
    bool isAddItem(QString url,QString title);
    void selectPlatfrom(QString name);




};

#endif // LIVE_H
