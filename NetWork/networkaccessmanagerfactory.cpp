/******************************************************************
    QML图片缓存
    engine.setNetworkAccessManagerFactory(new MyNetworkAccessManagerFactory);
******************************************************************/

#include "networkaccessmanagerfactory.h"

#include <QDir>

NetworkAccessManagerFactory::NetworkAccessManagerFactory()
{

}

NetworkAccessManagerFactory::~NetworkAccessManagerFactory()
{
    if(nam) delete nam;
    if(diskCache) delete diskCache;
}

QNetworkAccessManager *NetworkAccessManagerFactory::create(QObject *parent)
{
    nam = new QNetworkAccessManager(parent);
    diskCache = new QNetworkDiskCache(nam);

    QString cachePath = QStandardPaths::displayName(QStandardPaths::CacheLocation);

    //qDebug() << "cache path:" << cachePath;

    diskCache->setCacheDirectory(cachePath);
    diskCache->setMaximumCacheSize(100 * 1024 * 1024);   // 这里设置的缓存大小为 100 MB

    nam->setCache(diskCache);

    return nam;
}



/******************************************************************
    统计文件夹大小
******************************************************************/
qint64 NetworkAccessManagerFactory::dirSize(const QString &path)
{
    QDir dir(path);
    qint64 size = 0;
    foreach (QFileInfo fileInfo, dir.entryInfoList(QDir::Files)) {
        size += fileInfo.size();
    }

    foreach (QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        size += dirSize(path + QDir::separator() + subDir);
    }
    return size;
}
