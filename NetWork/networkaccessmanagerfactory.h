#ifndef NETWORKACCESSMANAGERFACTORY_H
#define NETWORKACCESSMANAGERFACTORY_H

#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QQmlNetworkAccessManagerFactory>


class NetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
    NetworkAccessManagerFactory();
    ~NetworkAccessManagerFactory();

    virtual QNetworkAccessManager *create(QObject *parent);
    qint64 dirSize(const QString &path);


private:
    QNetworkAccessManager *nam = NULL;
    QNetworkDiskCache* diskCache = NULL;
};

#endif // NETWORKACCESSMANAGERFACTORY_H
