#include "cookiejar.h"

CookieJar::CookieJar(QObject *parent)
    : QNetworkCookieJar(parent)
{

}

CookieJar::~CookieJar()
{
}

QList<QNetworkCookie> CookieJar::mycookies()
{
    return  this->allCookies();
}

void CookieJar::setCookies(const QList<QNetworkCookie>& cookieList)
{
    this->setAllCookies(cookieList);
}
