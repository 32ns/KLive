#include "userpay.h"
#include <QDebug>
#include <QSettings>

UserPay::UserPay(QObject *parent) : QThread(parent)
{
    QSettings settings("db.ini",QSettings::IniFormat,this);
    if(!settings.contains("DbServer"))
    {
        settings.setValue("DbServer","127.0.0.1");
        settings.setValue("DbPort",3306);
        settings.setValue("DbName","KLive");
        settings.setValue("DbUser","root");
        settings.setValue("DbPassword","root");
    }

    QString dbhost = settings.value("DbServer").toString();
    int dbPort = settings.value("DbPort").toInt();
    QString dbname = settings.value("DbName").toString();
    QString dbUser = settings.value("DbUser").toString();
    QString dbPassword = settings.value("DbPassword").toString();

    sql = new SqlManager(this);
    sql->connectSql(dbhost,dbPort,dbname,dbUser,dbPassword,"wechat");
}

UserPay::~UserPay()
{
    this->isExit = true;
    if(sql) delete sql;
}

void UserPay::run()
{
    while(!isExit)
    {
        if(m_PayQuquq.isEmpty())
        {
            msleep(1000);
            continue;
        }

        PayInfo pay = m_PayQuquq.dequeue();
        this->sumCheck(pay);
    }
}



/******************************************************************
    添加充值到列队
******************************************************************/
void UserPay::addPay(QString username, QString sum)
{
    PayInfo info;
    info.username = username;
    info.sum = sum;
    m_PayQuquq.enqueue(info);
}



/******************************************************************
    充值金额检测
******************************************************************/
void UserPay::sumCheck(UserPay::PayInfo info)
{
    qDebug()<<"收款信息到达";

    int day = sql->getDayOfPay(info.sum);

    if(day > 0)
    {
        this->pay(info,day);
    }else
    {
        sql->addFailure(info.username,info.sum,"没有找到对应支付金额");
        qDebug()<<"充值失败:"<<info.username<<info.sum<<"\t没有找到对应支付金额";
    }
}


/******************************************************************
    用户充值
******************************************************************/
void UserPay::pay(UserPay::PayInfo info,int Days)
{
    SqlManager::UserInfo user = sql->queryUserInfo(info.username);
    if(!user.username.isEmpty())
    {
        QDateTime etimer;
        if(user.endtimer > QDateTime::currentDateTime())
        {
            etimer = user.endtimer.addDays(Days);
        }else
        {
            etimer = QDateTime::currentDateTime().addDays(Days);
        }
        if(sql->userPay(info.username,etimer))
        {
            sql->paySucceed(info.username,info.sum);
        }
    }else
    {
        sql->addFailure(info.username,info.sum,"没有找到该用户");
        qDebug()<<"没有找到该用户:"<<info.username<<"\t没有找到该用户";
    }
}
























