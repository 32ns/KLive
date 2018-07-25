#include "global.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif

#include <QNetworkInterface>
#include <QCryptographicHash>
#include <QTime>

Global::Global()
{

}


/******************************************************************
    获取Mac
******************************************************************/
QString Global::getDeviceid()
{
    QString deviceID = "";

    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    for(int i = 0; i < nCnt; i ++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            deviceID = nets[i].hardwareAddress();
            break;
        }
    }

#ifdef Q_OS_ANDROID

    if(deviceID.isEmpty())
    {
        QAndroidJniObject myID = QAndroidJniObject::fromString("android_id");
        QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
        QAndroidJniObject appctx = activity.callObjectMethod("getApplicationContext","()Landroid/content/Context;");
        QAndroidJniObject contentR = appctx.callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");

        QAndroidJniObject androidId = QAndroidJniObject::callStaticObjectMethod("android/provider/Settings$Secure","getString",
                                                                             "(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;",
                                                                             contentR.object<jobject>(),
                                                                             myID.object<jstring>());

        deviceID = androidId.toString();
    }

#endif
    deviceID = QCryptographicHash::hash(deviceID.append("klivecn").toUtf8(),QCryptographicHash::Sha3_256).toBase64();
    return deviceID;
}


/******************************************************************
   返回Token
******************************************************************/
QByteArray Global::getToken()
{
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();   //将当前时间转为时间戳

    QString did = Global::getDeviceid();
    QString edid = did+"5201314"+timeT;
    QString token = QCryptographicHash::hash(edid.toUtf8(),QCryptographicHash::Md5).toBase64();

    QByteArray data;
    data.append("version_id=");
    data.append("1.01");
    data.append("&app_type=android");
    data.append("&dt=");
    data.append(QString::number(timeT));
    data.append("&did=");
    data.append(did);
    data.append("&token=");
    data.append(token);

    return data;
}

