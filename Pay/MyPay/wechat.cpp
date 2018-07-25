#include "wechat.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QXmlStreamReader>
#include <QTextCodec>

WeChat::WeChat(QObject *parent) : QObject(parent)
{
    m_SyncHostList.append("webpush.wx2.qq.com");
    m_SyncHostList.append("webpush.wx.qq.com");
    m_SyncHostList.append("webpush.weixin.qq.com");
    m_SyncHostList.append("webpush2.weixin.qq.com");
    m_SyncHostList.append("webpush.weixin.qq.com ");    
    m_SyncHostList.append("webpush.wx8.qq.com");    
    m_SyncHostList.append("webpush.web2.wechat.com");
    m_SyncHostList.append("webpush.web.wechat.com");

    this->m_SyncHost = m_SyncHostList[0];

    m_http = new HttpManager(this);
    connect(m_http,&HttpManager::sig_Finished,this,&WeChat::ReadFinished);

    syncTimer = new QTimer();
    connect(syncTimer,&QTimer::timeout,this,&WeChat::syncStatus);

    msgToMe = new QTimer();
    connect(msgToMe,&QTimer::timeout,this,&WeChat::sendMessageToMe);

    m_Pay = new UserPay(this);
    m_Pay->start();

}

WeChat::~WeChat()
{
    if(m_Pay)
    {
        m_Pay->terminate();
        delete m_Pay;
    }
    this->exitLogin();
    if(syncTimer) delete syncTimer;
    if(msgToMe) delete msgToMe;
    if(m_http) delete m_http;    
}


/******************************************************************
    开始
******************************************************************/
void WeChat::start()
{
    this->getUUID();
}


/******************************************************************
    生成设备ID
******************************************************************/
QString WeChat::getDeviceID()
{
    QString id("e");
    for(int i=0;i<15;i++)
    {
        id.append(QString::number(qrand()%10));
    }

    return id;
}



/******************************************************************
    获取时间戳
******************************************************************/
QString WeChat::getTimeID()
{
    QDateTime dt = QDateTime::currentDateTime();
    qint64 trmeT = dt.toTime_t();

    return QString::number(trmeT);
}



/******************************************************************
    UUID
******************************************************************/
void WeChat::getUUID()
{
    QString url("https://login.weixin.qq.com/jslogin?");
    url.append("appid=wx782c26e4c19acffb&redirect_uri=https%3A%2F%2Fwx.qq.com%2Fcgi-bin%2Fmmwebwx-bin%2Fwebwxnewloginpage&fun=new&lang=zh_CN");
    url.append("&_=").append(getTimeID());

    m_http->get(url,HttpManager::getUUID);
}


/******************************************************************
    返回UUID完成
******************************************************************/
void WeChat::getUUIDFinish(QByteArray data)
{
    if(data.isEmpty())
    {
        qDebug()<<"获取UUID失败!";
        return;
    }

    QRegExp exp("\\d+");
    exp.indexIn(data);
    QString code = exp.capturedTexts().last();
    if(code != "200")
    {
        qDebug()<<"获取UUID失败!"<< code;
        return;
    }

    QRegExp dxp("\"([^\"]*)\"");
    dxp.indexIn(data);

    current_UUID = dxp.capturedTexts().last();

    this->getQRCode(current_UUID);
}



/******************************************************************
    返回二唯码
******************************************************************/
void WeChat::getQRCode(QString uuid)
{
    QString url("https://login.weixin.qq.com/qrcode/");
    url.append(uuid);

    m_http->get(url,HttpManager::getQRCode);
}



/******************************************************************
    等待登陆
******************************************************************/
void WeChat::waitForLogin(QString uuid)
{
    QString url("https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?tip=0");
    url.append("&uuid=").append(uuid);
    url.append("&_=").append(getTimeID());

    m_http->get(url,HttpManager::waitForLogin);
}


/******************************************************************
    等登陆结果
******************************************************************/
void WeChat::waitForLoginFinish(QByteArray data)
{
    QRegExp exp("\\d+");
    exp.indexIn(data);
    QString code = exp.capturedTexts().last();
    switch (code.toInt()) {
    case 408:{

        qDebug()<<"登陆超时!";
        this->getQRCode(current_UUID);

    }break;

    case 201:{

        qDebug()<<"扫描成功";
        this->waitForLogin(current_UUID);

    }break;

    case 200:{

        qDebug()<<"登陆成功! \n";

        QRegExp dxp("\"([^\"]*)\"");
        dxp.indexIn(data);

        QString loginurl = dxp.capturedTexts().last();
        this->getLoginInfo(loginurl);

    }break;


    default:{
        qDebug()<<"登陆异常\n"<<data;
    }break;

    }
}


/******************************************************************
获取登陆信息
******************************************************************/
void WeChat::getLoginInfo(QString url)
{
    QUrl curl(url);
    m_currentHost = curl.host();

    url.append("&fun:new");
    m_http->get(url,HttpManager::getLoginInfo);
}


/******************************************************************
  返回登陆信息完成
******************************************************************/
void WeChat::getLoginInfoFinish(QByteArray data)
{
    m_loginInfo.clear();
    QXmlStreamReader reader(data);
    while(!reader.atEnd())
    {
        if(reader.isStartElement())
        {
            if(reader.name()=="ret")
            {
                m_loginInfo.insert("ret",reader.readElementText());
            }else if(reader.name()=="message")
            {
                m_loginInfo.insert("message",reader.readElementText());

            }else if(reader.name()=="skey")
            {
                m_loginInfo.insert("skey",reader.readElementText());

            }else if(reader.name()=="wxsid")
            {
                m_loginInfo.insert("wxsid",reader.readElementText());

            }else if(reader.name()=="wxuin")
            {
                m_loginInfo.insert("wxuin",reader.readElementText());

            }else if(reader.name()=="pass_ticket")
            {
                m_loginInfo.insert("pass_ticket",reader.readElementText());

            }else if(reader.name()=="isgrayscale")
            {
                m_loginInfo.insert("isgrayscale",reader.readElementText());
            }
        }

        reader.readNext();
    }

    userInit();
}


/******************************************************************
    初始化用户信息
******************************************************************/
void WeChat::userInit()
{
    QString url("https://");
    url.append(this->m_currentHost);
    url.append("/cgi-bin/mmwebwx-bin/webwxinit?pass_ticket=").append(m_loginInfo.value("pass_ticket"));
    url.append("&skey=").append(m_loginInfo.value("skey"));
    url.append("&r=").append(this->getTimeID());

    QJsonObject json;
    json.insert("Uin",m_loginInfo.value("wxuin"));
    json.insert("Sid",m_loginInfo.value("wxsid"));
    json.insert("Skey",m_loginInfo.value("skey"));
    json.insert("DeviceID",this->getDeviceID());

    QJsonObject baseRequest;
    baseRequest.insert("BaseRequest",json);
    QJsonDocument jd(baseRequest);

    m_BaseRequest = json;

    m_http->post(url,jd.toJson(),HttpManager::userInit);
}


/******************************************************************
    初始化用户信息完成
******************************************************************/
void WeChat::userInitFinish(QByteArray data)
{
    QJsonObject json = QJsonDocument::fromJson(data).object();

    m_UserInfo = json.value("User").toObject();

    m_SyncKey = json.value("SyncKey").toObject();

    statusNotify();
}


/******************************************************************
  开启微信状态通知
  客户端读取消息后要发起请求, 告诉服务器消息已经读取, 从而通知手机客户端
******************************************************************/
void WeChat::statusNotify()
{
    QString url("https://");
    url.append(this->m_currentHost).append("/cgi-bin/mmwebwx-bin/webwxstatusnotify?lang=zh_CN");
    url.append("&pass_ticket=").append(m_loginInfo.value("pass_ticket"));

    QJsonObject json;
    json.insert("BaseRequest",m_BaseRequest);
    json.insert("Code",3);
    json.insert("FromUserName",m_UserInfo.value("UserName").toString());
    json.insert("ToUserName",m_UserInfo.value("UserName").toString());
    json.insert("ClientMsgId",this->getTimeID());

    QJsonDocument jd(json);

    m_http->post(url,jd.toJson(),HttpManager::statusNotifyFinish);
}

/******************************************************************
  更新完成
******************************************************************/
void WeChat::statusNotifyFinish(QByteArray data)
{
    Q_UNUSED(data);

    syncStatus();
}


/******************************************************************
  同步状态
******************************************************************/
void WeChat::syncStatus()
{
    QString sk;
    QJsonArray ja = m_SyncKey.value("List").toArray();
    for(int i=0;i<ja.count();i++)
    {
        int key = ja[i].toObject().value("Key").toInt();
        int val = ja[i].toObject().value("Val").toInt();
        QString kv = QString::number(key)+"_"+QString::number(val);
        if(i<ja.count()-1)
        {
            kv.append("|");
        }
        sk.append(kv);
    }


    QString url("https://");
    url.append(m_SyncHost).append("/cgi-bin/mmwebwx-bin/synccheck?");
    url.append("r=").append(getTimeID());
    url.append("&sid=").append(m_loginInfo.value("wxsid"));
    url.append("&uin=").append(m_loginInfo.value("wxuin"));
    url.append("&skey=").append(m_loginInfo.value("skey"));
    url.append("&deviceid=").append(this->getDeviceID());
    url.append("&synckey=").append(sk);
    url.append("&_=").append(getTimeID());

    m_http->get(url,HttpManager::syncStatus);
}


/******************************************************************
同步状态完成

retcode:
0正常
1100失败/登出微信
selector:
0正常
2新的消息
4通过时发现,删除好友
6删除时发现和对方通过好友验证
7进入/离开聊天界面(可能没有了)
******************************************************************/
void WeChat::syncStatusFinish(QByteArray data)
{
    QString allcode = data;
    allcode = allcode.section("{",1);
    allcode = allcode.left(allcode.length()-1);
    QStringList codelist = allcode.split(",");

    qDebug()<<codelist<<"\n";

    if(codelist.count()<2)
    {
        return;
    }

    if(codelist[0] != "retcode:\"0\"")
    {
        if(!syncTimer->isActive())
        {
            if(currentHostListjs < m_SyncHostList.count()-1)
            {
                currentHostListjs++;
                m_SyncHost = m_SyncHostList[currentHostListjs];
                this->syncStatus();
            }else
            {
                qDebug()<<"同步状态失败,程序停止!"<<m_SyncHost;
                qDebug()<<data;
            }
        }


    }else
    {
        if(!syncTimer->isActive())
        {
            qDebug()<<"同步成功! "<<m_SyncHost;
            this->syncTimer->start(5000);
            this->msgToMe->start(60000*5);
        }
    }

    if(codelist[1] != "selector:\"0\"")
    {
        this->syncMesasge();
    }


}


/******************************************************************
    同步消息
******************************************************************/
void WeChat::syncMesasge()
{
    QString url("https://");
    url.append(this->m_currentHost);
    url.append("/cgi-bin/mmwebwx-bin/webwxsync?");
    url.append("sid=").append(m_loginInfo.value("wxsid"));
    url.append("&skey=").append(m_loginInfo.value("skey"));
    url.append("&pass_ticket=").append(m_loginInfo.value("pass_ticket"));

    QJsonObject json;
    json.insert("BaseRequest",this->m_BaseRequest);
    json.insert("SyncKey",this->m_SyncKey);
    json.insert("rr",this->getTimeID());

    QJsonDocument jd(json);
    m_http->post(url,jd.toJson(),HttpManager::syncMessage);
}


/******************************************************************
    同步消息完成
******************************************************************/
void WeChat::syncMesasgeFinish(QByteArray data)
{
    QJsonDocument jd = QJsonDocument::fromJson(data);
    QJsonObject json = jd.object();
    this->m_SyncKey = json.value("SyncKey").toObject();
    QJsonArray msglist = json.value("AddMsgList").toArray();     

    for(int i=0;i<msglist.count();i++)
    {
        QJsonObject msg = msglist[i].toObject();
        QString retmsg =  msg.value("Content").toString();

        if(!retmsg.isEmpty())
        {            
            if(retmsg.contains("收款金额"))
            {
                qDebug()<<"您有新短消息,请注意查收 \t"<<QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")<<"\n\n";

                QString sum,username;

                QRegExp jr("收款金额：￥(\\d+\\.\\d+)<br/>");
                jr.indexIn(retmsg);
                if(jr.capturedTexts().count() > 1)
                {
                    sum = jr.capturedTexts()[1];
                }

                QRegExp bz("付款方备注：(\\w*)<br/>");
                bz.indexIn(retmsg);
                if(bz.capturedTexts().count() > 1)
                {
                    username = bz.capturedTexts()[1];
                }

                if(!sum.isEmpty())
                {
                    m_Pay->addPay(username,sum);
                }
                qDebug()<<"收到:"<<username<<sum;
            }else
            {
                qDebug()<<retmsg<<"\n";
            }
        }
    }


}


/******************************************************************
    发送消息
******************************************************************/
void WeChat::sendMessage(QString ToUserName,QString msg)
{
    QString url("https://");
    url.append(m_currentHost).append("/cgi-bin/mmwebwx-bin/webwxsendmsg?lang=zh_CN");
    url.append("&pass_ticket=").append(m_loginInfo.value("pass_ticket"));

    QString cid = QString::number(QDateTime::currentDateTime().toTime_t()<<4);
    cid.append(QString::number(qrand()%10)).append(QString::number(qrand()%10));
    cid.append(QString::number(qrand()%10)).append(QString::number(qrand()%10));
    cid.append(QString::number(qrand()%10)).append(QString::number(qrand()%10));
    cid.append(QString::number(qrand()%10));

    QJsonObject objmsg;
    objmsg.insert("Type",1);
    objmsg.insert("Content",msg);
    objmsg.insert("FromUserName",m_UserInfo.value("UserName").toString());
    objmsg.insert("ToUserName",ToUserName);
    objmsg.insert("LocalID",cid);
    objmsg.insert("ClientMsgId",cid);

    QJsonObject json;
    json.insert("BaseRequest",m_BaseRequest);
    json.insert("Msg",objmsg);
    json.insert("Scene",0);
    QJsonDocument jd(json);
    m_http->post(url,jd.toJson(),HttpManager::sendMessage);
}


/******************************************************************
    发送消息完成
******************************************************************/
void WeChat::sendMessageFinish(QByteArray data)
{
    qDebug()<<"\n\n"<<data;
}



/******************************************************************
    给自己发送消息
******************************************************************/
void WeChat::sendMessageToMe()
{
    QString tm = QDateTime::currentDateTime().toString("dd HH:mm:ss");
    sendMessage(m_UserInfo.value("UserName").toString(),tm+"  我还在...");
}


/******************************************************************
    读取完成
******************************************************************/
void WeChat::ReadFinished(QByteArray data,HttpManager::ReadCmd cmd)
{
    switch (cmd) {

    case HttpManager::getUUID:{
        this->getUUIDFinish(data);
    }break;

    case HttpManager::getQRCode:{

        emit sig_QRcodeArrive(data);
        this->waitForLogin(this->current_UUID);

    }break;

    case HttpManager::waitForLogin:{
        this->waitForLoginFinish(data);
    }break;

    case HttpManager::getLoginInfo:{
        this->getLoginInfoFinish(data);
    }break;

    case HttpManager::userInit:{
        this->userInitFinish(data);
    }break;

    case HttpManager::statusNotifyFinish:{
        this->statusNotifyFinish(data);
    }break;

    case HttpManager::syncStatus:{
        this->syncStatusFinish(data);
    }break;

    case HttpManager::syncMessage:{
        this->syncMesasgeFinish(data);
    }break;

    case HttpManager::sendMessage:{
        this->sendMessageFinish(data);
    }break;


    default:    qDebug()<<data<<"\n\n";
        break;
    }
}


/******************************************************************
    退出登陆
******************************************************************/
void WeChat::exitLogin()
{
    QString url("https://");
    url.append(m_currentHost).append("/cgi-bin/mmwebwx-bin/webwxlogout?redirect=1&type=1");
    url.append("&skey=").append(m_loginInfo.value("skey"));

    QByteArray data;
    data.append("sid=").append(m_loginInfo.value("wxsid"));
    data.append("&uin=").append(m_loginInfo.value("wxuin"));

    m_http->post(url,data,HttpManager::exitLogin);
}






















