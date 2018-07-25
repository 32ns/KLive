/******************************************************************
    E4A能用RC4
******************************************************************/

#include "rc4.h"
#include <QDebug>
#include <iomanip>

Rc4::Rc4(QObject *parent) : QObject(parent)
{


}

Rc4::~Rc4()
{

}


/******************************************************************
    解密
******************************************************************/
QString Rc4::Decrypt(QString input, QString pass)
{
    QString tmp;
    for(int i=0;i<input.length();i++)
    {
        if(i&1)
        {
            bool a;
            tmp.append((QString)input.mid(i-1,2).toInt(&a,16));
        }
    }

    unsigned char * ret = rc4Decrypt((unsigned char*)tmp.toLatin1().data(), (unsigned char*)pass.toLatin1().data());

    QString retstr;
    retstr = QString::fromLocal8Bit((char*)ret);

    return retstr;
}



unsigned char * Rc4::rc4Encrypt(unsigned char * ByteInput, unsigned char * pwd) // Takes in bytes to decrypt, seed, and variable name to store end result
{
    unsigned char * temp;
    int i, j = 0, t, tmp, tmp2, s[256], k[256];
    for (tmp = 0; tmp < 256; tmp++) {
        s[tmp] = tmp;
        k[tmp] = pwd[(tmp % strlen((char *)pwd))];
    }
    for (i = 0; i < 256; i++) {
        j = (j + s[i] + k[i]) % 256;
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    cout << endl << endl;
    temp = new unsigned char[(int)strlen((char *)ByteInput) + 1];
    i = j = 0;
    for (tmp = 0; tmp < (int)strlen((char *)ByteInput); tmp++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        tmp2 = s[i];
        s[i] = s[j];
        s[j] = tmp2;
        t = (s[i] + s[j]) % 256;
        if (s[t] == ByteInput[tmp])
        {
            temp[tmp] = ByteInput[tmp];
        }
        else
        {
            temp[tmp] = s[t] ^ ByteInput[tmp];
        }
    }
    QString ret;
    for (tmp = 0; tmp < (int)strlen((char *)ByteInput); tmp++) {
        ret.append(QString::number(temp[tmp],16));
    }
    return temp;
}

unsigned char * Rc4::rc4Decrypt(unsigned char * ByteInput, unsigned char * pwd) // Takes in bytes to decrypt, seed, and variable name to store end result
{
    unsigned char * temp;
    int i, j = 0, t, tmp, tmp2, s[256], k[256];
    for (tmp = 0; tmp < 256; tmp++) {
        s[tmp] = tmp;
        k[tmp] = pwd[(tmp % strlen((char *)pwd))];
    }
    for (i = 0; i < 256; i++) {
        j = (j + s[i] + k[i]) % 256;
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    cout << endl << endl;
    temp = new unsigned char[(int)strlen((char *)ByteInput) + 1];
    i = j = 0;
    for (tmp = 0; tmp < (int)strlen((char *)ByteInput); tmp++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        tmp2 = s[i];
        s[i] = s[j];
        s[j] = tmp2;
        t = (s[i] + s[j]) % 256;
        if (s[t] == ByteInput[tmp])
        {
            temp[tmp] = ByteInput[tmp];
        }
        else
        {
            temp[tmp] = s[t] ^ ByteInput[tmp];
        }
    }

    return temp;
}





