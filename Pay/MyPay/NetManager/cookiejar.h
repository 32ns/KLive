#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include<QObject>
#include<QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkCookie>

class CookieJar :public QNetworkCookieJar
{
public:
    CookieJar(QObject *parent = 0);
    ~CookieJar();
    QList<QNetworkCookie> mycookies();
    void setCookies(const QList<QNetworkCookie>& cookieList);
};

#endif // COOKIEJAR_H
