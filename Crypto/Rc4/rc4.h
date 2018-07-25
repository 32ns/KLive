#ifndef RC4_H
#define RC4_H

#include <QObject>
#include <iostream>
using namespace::std;

class Rc4 : public QObject
{
    Q_OBJECT
public:
    explicit Rc4(QObject *parent = nullptr);
    ~Rc4();

private:

signals:

public slots:
    QString Decrypt(QString input,QString pass);

private slots:
    unsigned char * rc4Encrypt(unsigned char * ByteInput, unsigned char * pwd);
    unsigned char * rc4Decrypt(unsigned char * ByteInput, unsigned char * pwd);
};

#endif // RC4_H
