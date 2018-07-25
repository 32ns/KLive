#ifndef USERPAY_H
#define USERPAY_H

#include <QObject>
#include <QQueue>
#include "SqlManager/sqlmanager.h"
#include <QThread>

class UserPay : public QThread
{
public:
    struct PayInfo
    {
        QString username;
        QString sum;
    };

    Q_OBJECT
public:
    explicit UserPay(QObject *parent = nullptr);
    ~UserPay();

private:
    SqlManager *sql = NULL;
    QQueue<PayInfo> m_PayQuquq;
    bool isExit = false;

signals:


protected:
    void run();

public slots:
    void addPay(QString username,QString sum);
    void sumCheck(PayInfo info);
    void pay(PayInfo info,int Days);
};

#endif // USERPAY_H
