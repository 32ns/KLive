#include "sqlmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

SqlManager::SqlManager(QObject *parent) : QObject(parent)
{

}

SqlManager::~SqlManager()
{

}



/******************************************************************
    返回支付对应天数
******************************************************************/
int SqlManager::getDayOfPay(QString sum)
{
    int dy = 0;
    QString sql("select * from db_Pay where sum = '");
    sql.append(sum).append("'");

    QSqlQuery query(db);
    if(!query.exec(sql))
    {
        qDebug()<<"查询支付对应表失败!";
        return dy;
    }

    while (query.next()) {
        dy = query.value("day").toInt();
    }

    return dy;
}

bool SqlManager::connectSql(QString host,int port,QString dbname,QString username,QString password,QString connectname)
{
    db = QSqlDatabase::addDatabase("QMYSQL",connectname);
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);
    if(!db.open())
    {
        qDebug()<<"打开数据库失败!";
        return false;
    }

    qDebug()<<"打开数据库成功!"<<connectname;

    return true;
}



/******************************************************************
    查询用户信息
******************************************************************/
SqlManager::UserInfo SqlManager::queryUserInfo(QString username)
{
    QSqlQuery query(db);

    QString sql("select * from db_User where username='");
    sql.append(username).append("'");

    UserInfo user;
    if(!query.exec(sql))
    {
        qDebug()<<"查询用户信息失败!"<<query.lastError().text();
    }

    while (query.next()) {

        user.id = query.value("id").toInt();
        user.username = query.value("username").toString();
        user.password = query.value("password").toString();
        user.begintimer = query.value("begintimer").toDateTime();
        user.endtimer = query.value("endtimer").toDateTime();
        user.regtimer = query.value("regtimer").toDateTime();
        user.deviceid = query.value("deviceid").toString();
    }

    return user;
}


/******************************************************************
    用户充值
******************************************************************/
bool SqlManager::userPay(QString username,QDateTime endtimer)
{
    QSqlQuery query(db);

    QString sql = "UPDATE db_User set endtimer='";
    sql.append(endtimer.toString("yyyy-MM-dd HH:mm:ss")).append("' where username='");
    sql.append(username).append("'");

    if(!query.exec(sql))
    {
        qDebug()<<"用户充值失败!"<<query.lastError().text();
        return false;
    }

    qDebug()<<"用户充值成功!"<<username<<":"<<endtimer.toString("yyyy-MM-dd HH:mm:ss");
    return true;
}



/******************************************************************
    充值成功
******************************************************************/
void SqlManager::paySucceed(QString username, QString sum)
{
    QSqlQuery query(db);
    QString sql("insert into db_PaySucceed set username='");
    sql.append(username).append("',sum='").append(sum).append("',paydate='");
    sql.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")).append("'");

    if(!query.exec(sql))
    {
        qDebug()<<"添加充值成功记录失败!"<<query.lastError().text();
        return;
    }
    qDebug()<<"添加充值成功记录完成"<<QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}


/******************************************************************
    充值失败
******************************************************************/
void SqlManager::addFailure(QString username, QString sum,QString msg)
{
    QSqlQuery query(db);
    QString sql("insert into db_PayFailure set username='");
    sql.append(username).append("',sum='").append(sum).append("',msg='");
    sql.append(msg).append("',paydate='");
    sql.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")).append("'");

    if(!query.exec(sql))
    {
        qDebug()<<"添加充值失败失败!"<<query.lastError().text();
        return;
    }
    qDebug()<<"记录用户充值失败完成"<<QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}







