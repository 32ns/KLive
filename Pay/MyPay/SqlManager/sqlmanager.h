#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QDateTime>
#include <QObject>
#include <QtSql/QSqlDatabase>

class SqlManager : public QObject
{
public:
    struct UserInfo
    {
        int id;
        QString username;   //用户名
        QString password;   //密码
        QDateTime begintimer;   //开始时间
        QDateTime endtimer;     //结束时间
        QDateTime regtimer;     //注册时间
        QString deviceid;   //设备id
    };



    Q_OBJECT
public:
    explicit SqlManager(QObject *parent = nullptr);
    ~SqlManager();

private:
    QSqlDatabase db;

signals:

public slots:
    int getDayOfPay(QString sum);
    bool connectSql(QString host,int port,QString dbname,QString username,QString password,QString connectname);
    UserInfo queryUserInfo(QString username);
    bool userPay(QString username,QDateTime endtimer);
    void paySucceed(QString username,QString sum);
    void addFailure(QString username,QString sum,QString msg);

};

#endif // SQLMANAGER_H
