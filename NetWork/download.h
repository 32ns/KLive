#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(QObject *parent = nullptr);
    ~Download();

private:
    QNetworkAccessManager *NetManager = NULL;
    QNetworkReply *Reply = NULL;
    QFile *File = NULL;

signals:
    void sig_DownLoadFinish(QString filename);
    void sig_downloadProgress(double all,double current);

public slots:
    bool startDown(QUrl url);
    void readyRead();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void finished();
};

#endif // DOWNLOAD_H
