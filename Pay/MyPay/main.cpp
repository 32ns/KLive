#include <QCoreApplication>
#include <QDir>
#include <pay.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString strLibPath(QDir::toNativeSeparators(QCoreApplication::applicationDirPath())+QDir::separator()+"plugins");
    a.addLibraryPath(strLibPath);

    QScopedPointer<Pay> pay(new Pay());

    return a.exec();
}
