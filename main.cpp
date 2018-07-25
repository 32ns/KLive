#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <NetWork/networkaccessmanagerfactory.h>
#include <QtQml>
#include "live.h"

int main(int argc, char *argv[])
{    
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QCoreApplication::setOrganizationName("KLive");
    QCoreApplication::setOrganizationDomain("KLive");
    QCoreApplication::setApplicationName("KLive");


    Live live;

    QQmlApplicationEngine engine;

    engine.setNetworkAccessManagerFactory(new NetworkAccessManagerFactory); //开启缓存
    engine.rootContext()->setContextProperty("Live",&live);
    engine.rootContext()->setContextProperty("model_Ad",live.model_ad);
    engine.rootContext()->setContextProperty("model_Room",live.roomModel);
    engine.rootContext()->setContextProperty("model_roomItemModel",live.roomItemModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
