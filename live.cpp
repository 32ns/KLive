#include "live.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtAV>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QZXing.h>
#include "Platfrom/linju.h"

using namespace QtAV;

Live::Live(QObject *parent) : QObject(parent)
{
    QtAV::setLogLevel(LogOff);

    settings = new QSettings("KLive");
    roomItemModel = new Model_RoomItem(this);
    roomModel = new Model_RoomList(this);
    model_ad = new AdModel(this);


    m_Http = new HttpManager(this);
    connect(m_Http,&HttpManager::sig_ReadFinish,this,&Live::readFinish);

    this->init();

}

Live::~Live()
{
    if(m_pingtai) delete m_pingtai;
    if(download) delete download;
    if(settings) delete settings;
    if(model_ad) delete model_ad;
    if(roomItemModel) delete roomItemModel;
    if(roomModel) delete roomModel;
    if(m_Http) delete m_Http;
}


/******************************************************************
  初始化
******************************************************************/
void Live::init()
{
    qRcodePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation).append("/klive.png");

    QByteArray data = Global::getToken();
    qDebug()<<data;
    m_Http->post(homeUrl+"init.php",data,READCMD::Init);
}



/******************************************************************
    拿到读取来的信息
******************************************************************/
void Live::readFinish(QByteArray data, READCMD cmd)
{
    switch (cmd) {

    //初始化信息
    case READCMD::Init : {
        this->serverMessage(data);
    }break;


    case READCMD::UserLogin : {
        this->serverMessage(data);
    }break;


    case READCMD::UserReg : {
        this->serverMessage(data);
    }break;


    default:
        break;
    }
}


/******************************************************************
    返回用户状态 roomname房间名,查询完状态以后要获取这个房间的列表
******************************************************************/
void Live::getUserState(QString roomname)
{
    this->currentRoomName = roomname;

    //如果用户没有登陆
    if(!settings->contains("username") || !settings->contains("password"))
    {
        emit sig_UserState(0,"没有登陆");
    }else
    {
        QString username = settings->value("username").toString();
        QString password = settings->value("password").toString();
        this->loginUser(username,password);
    }
}


/******************************************************************
    用户登陆
******************************************************************/
void Live::loginUser(QString user, QString password)
{    
    QByteArray data = Global::getToken();
    data.append("&user=");
    data.append(user);
    data.append("&password=");
    data.append(password);
    data.append("&type=login");
    m_Http->post(homeUrl+"user.php",data,READCMD::UserLogin);
}


/******************************************************************
    用户注册
******************************************************************/
void Live::regUser(QString user, QString password)
{
    QString pass = QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5).toBase64();
    QByteArray data = Global::getToken();
    data.append("&user=");
    data.append(user);
    data.append("&password=");
    data.append(pass);
    data.append("&type=reg");
    m_Http->post(homeUrl+"user.php",data,READCMD::UserReg);
}



/******************************************************************
    服务器消息解析  401参数不合法 402获取用户信息失败 403获取类型失败
    405连接数据出错 200获取用户信息成功 404用户或密码错误 201注册成功
    202注册失败 203用户名已经被占用 204设备已被注册
******************************************************************/
void Live::serverMessage(QByteArray data)
{
    QJsonDocument jd = QJsonDocument::fromJson(data);
    QJsonObject obj = jd.toVariant().toJsonObject();
    int cmd = obj.value("code").toInt();
    switch (cmd) {
    case 1 : {  //发现新版本        
        QJsonObject jsobj = obj.value("data").toObject();
        QJsonDocument jsjd = QJsonDocument(jsobj);
        updateMessage(jsjd.toJson());
    }break;

    case 2 : {  //初始化信息到达

        QJsonObject json = obj.value("data").toObject();
        QString url = json.value("url").toString();
        selectPlatfrom(url);


        QJsonArray ja = json.value("ad").toArray();
        model_ad->clear();
        for(int i=0;i<ja.count();i++)
        {
            QJsonArray json = ja.at(i).toArray();
            AdModel::AdInfo info;
            info.title = json.at(1).toString();
            info.img = json.at(2).toString();
            info.url = json.at(3).toString();
            model_ad->addData(info);
        }

        QString topupUrl = json.value("topup").toString();
        settings->setValue("topup",topupUrl);

        QJsonObject appinfo = json.value("appinfo").toObject();
        QString appurl = appinfo.value("app_url").toString();
        settings->setValue("appurl",appurl);
        QImage img = QZXing::encodeData(appurl);
        img.save(qRcodePath);


    }break;

    case 404 : {
        emit sig_UserState(404,"用户名或密码错误!");
    }break;

    case 200 : {
        this->userLoadSucceecd(data);
    }break;

    case 201 :  {
        this->userLoadSucceecd(data);
    }break;

    case 203 : {
        emit sig_UserState(203,"用户名已经被占用");
    }break;

    case 204 : {
        QJsonObject json = obj.value("data").toObject();
        QString username = json.value("username").toString();
        emit sig_UserState(204,"设备已被注册,注册用户为:"+username);
    }break;



    default:
        break;
    }

}


/******************************************************************
     用户登陆成功
******************************************************************/
void Live::userLoadSucceecd(QByteArray data)
{
    QJsonDocument jd = QJsonDocument::fromJson(data);
    QJsonArray ja = jd.toVariant().toJsonObject().value("data").toArray();
    if(ja.count() > 0)
    {
        QJsonObject json = ja.at(0).toObject();
        QDateTime btimer = json.value("begintimer").toVariant().toDateTime();
        QDateTime etimer = json.value("endtimer").toVariant().toDateTime();
        QDateTime ctimer = QDateTime::currentDateTime();

        settings->setValue("username" , json.value("username").toString());
        settings->setValue("password" , json.value("password").toString());
        settings->setValue("begintimer" , btimer);
        settings->setValue("endtimer" , etimer);
        settings->setValue("regtimer" , json.value("regtimer").toVariant().toDateTime());
        settings->setValue("deviceid",json.value("deviceid").toString());
        settings->sync();        


        if(ctimer.secsTo(etimer) > 0)
        {
            this->getRoomItem(currentRoomName);
            emit sig_UserState(888,"登陆成功");
        }else
        {
            emit sig_UserState(999,"用户已到期");
        }
    }

}


/******************************************************************
    密码加密
******************************************************************/
QString Live::getPassCrypto(QString pass)
{
    return QCryptographicHash::hash(pass.toUtf8(),QCryptographicHash::Md5).toBase64();
}


/******************************************************************
    返回用户名给QML
******************************************************************/
QString Live::getUserInfo_username()
{
    if(settings->value("password").toString().length() > 0)
    {
        return settings->value("username").toString();
    }

    return "未登陆";
}


/******************************************************************
    返回到期时间给QML
******************************************************************/
QString Live::getUserInfo_endtimer()
{
    if(settings->contains("endtimer") && settings->value("password").toString().length() > 0)
    {
        return settings->value("endtimer").toDateTime().toString("yyyy-MM-dd");
    }

    return "";
}


/******************************************************************
    返回充值地址
******************************************************************/
QString Live::getTopUpUrl()
{
    return settings->value("topup").toString();
}



/******************************************************************
    获取房间列表
******************************************************************/
void Live::getRoomList()
{
    m_pingtai->getRoomList();
}


/******************************************************************
    获取房间列表完成
******************************************************************/
void Live::getRoomFinish(QList<Platfrom::PlatfromInfo> infolist)
{
    roomModel->clear();
    for(int i=0; i<infolist.count(); i++)
    {
        Platfrom::PlatfromInfo pt = infolist.at(i);
        Model_RoomList::RoomInfo info;
        info.platform = pt.name;
        info.image = pt.logo;
        info.address = pt.address;
        info.anchor = pt.number;
        roomModel->addRoom(info);
    }

}



/******************************************************************
    返回房间列表项
******************************************************************/
void Live::getRoomItem(QString roomname)
{
    if(m_pingtai){

        m_pingtai->getRoomItem(roomname);

    }
}


/******************************************************************
    返回房间列表项完成
******************************************************************/
void Live::getRoomItemFinish(QList<Platfrom::PlatfromItem> itemlist)
{
    roomItemModel->clear();

    Platfrom::PlatfromItem meItem;
    meItem.name = "KLive下载";
    meItem.url = "klive";
    meItem.logo = "file://"+qRcodePath;
    itemlist.insert(0,meItem);

    for(int i=0;i<itemlist.count(); i++)
    {
        Platfrom::PlatfromItem item = itemlist.at(i);
        Model_RoomItem::ItemInfo info;
        info.index = i;
        info.name = item.name;
        info.image = item.logo;
        info.rtmp = item.url;
        if(isAddItem(info.rtmp,info.name))
        {
            roomItemModel->addItem(info);
        }
    }

    emit sig_RoomItemCreateSucceed(currentRoomName,roomItemModel->rowCount());
}


/******************************************************************
    发现新版本
******************************************************************/
void Live::updateMessage(QByteArray data)
{
    QJsonDocument jd = QJsonDocument::fromJson(data);
    QJsonObject json = jd.toVariant().toJsonObject();
    QString versionid = json.value("version_id").toString();
    QString message = json.value("message").toString();
    QString msg = "发现新版本: "+versionid + "\n"+message;
    updateUrl = json.value("app_url").toString();
    msg.append("\n");
    emit sig_Update(msg,updateUrl);
}


/******************************************************************
    开始更新
******************************************************************/
void Live::startUpdate()
{
    if(download == NULL)
    {
        download = new Download(this);
        connect(download,&Download::sig_downloadProgress,this,&Live::sig_downloadProgress);
        connect(download,&Download::sig_DownLoadFinish,this,&Live::installApp);
    }
    download->startDown(QUrl(this->updateUrl));
}


/******************************************************************
    检测用户是否到期-本地 false没到期 true到期了
******************************************************************/
bool Live::checkUserDate()
{
    bool isOk = true;
    QDateTime ctimer = QDateTime::currentDateTime();
    QDateTime etimer = settings->value("endtimer").toDateTime();

    if(ctimer.secsTo(etimer) > 0)
    {
        isOk = false;
    }

    return isOk;
}


/******************************************************************
    是否添加这个Item
******************************************************************/
bool Live::isAddItem(QString url,QString title)
{
    QString itemlist;
    itemlist.append("http://t.cn/R3VRALE");
    itemlist.append("http://t.cn/R1UkzNv");
    itemlist.append("http://t.cn/R1ylnvJ");
    itemlist.append("http://t.cn/RuFjXPX");
    itemlist.append("http://t.cn/R1UDey");
    itemlist.append("http://t.cn/R14Pg2A");
    itemlist.append("http://t.cn/R3lvUJP");
    itemlist.append("*最新下载地址");
    itemlist.append("乐库");
    itemlist.append("官方推荐宝盒续费");
    itemlist.append("广告招商");

    if(itemlist.contains(url)||itemlist.contains(title))
    {
        return false;
    }

    return true;
}


/******************************************************************
    选择平台    rd邻居家的耳朵
******************************************************************/
void Live::selectPlatfrom(QString name)
{
    if(m_pingtai)
    {
        return;

    }else if(name=="rd")
    {
        m_pingtai = new LinJu(this);

    }



    if(m_pingtai)
    {
        connect(m_pingtai,&Platfrom::sig_GetRoomFinish,this,&Live::getRoomFinish);
        connect(m_pingtai,&Platfrom::sig_GetRoomItemFinish,this,&Live::getRoomItemFinish);
        this->getRoomList();
    }
}


/******************************************************************
    更新包下载完成
******************************************************************/
void Live::installApp(QString filename)
{
    qDebug()<<filename;
}


