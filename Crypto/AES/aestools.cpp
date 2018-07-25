#include "aestools.h"
#include <QDebug>

AESTools::AESTools(QByteArray key)
{
    if(key.size() != 16)
    {
       char keys[17] = "\0";
        for(int i = 0;i < 16;i++)
        {
            keys[i] = key.at(i % key.size());
        }
        keys[16] = '\0';
        crijndael.MakeKey(keys,"");
    } else{
        crijndael.MakeKey(key.data(),"");
    }
}

QByteArray AESTools::Decrypt(const QByteArray hexData)
{
    char *da = NULL;
    try{

        int length = hexData.size()+1;
        da = new char[length * 2];
        crijndael.Decrypt(hexData.data(), da, length-1);
        int max = 0;
        for(int i = length - 2;i > -1;i--){
            if(da[i] <= '\x10' && da[i] >= '\x00'){
                da[i] = 0;
                max++;
            } else{
                break;
            }
        }
        QByteArray r2 = QByteArray(da);
        delete[] da;
        da = NULL;
        return r2;

    }catch(QString exc){
        if(da != NULL){
            delete []da;
        }
        return NULL;
    }
}

QString* AESTools::Encrypt(const QString * data)
{
    char* p_data = NULL;
    char *szDataOut = NULL;
    try{
        //待加密字节数
        int length=data->toUtf8().size();
        //块数
        int block_num=length/16;
        if(length%16)
        {
            block_num++;
        }
        //构造加密块,padding方式为PKCS7,加密过程中，使用的块
        p_data=new char[block_num*16+1];
        memset(p_data,0x00,block_num*16+1);
        memcpy(p_data, data->toUtf8().data(), length);
        //padding块前一部分长度
        int k=length%16;
        //不padding块数
        int j=length/16;
        //padding块后一部分长度
        int padding=16-k;
        for(int i=0;i<padding;i++)
        {
            p_data[j*BLOCK_SIZE+k+i]=padding;
        }
        p_data[j*BLOCK_SIZE+k+padding]='\0';
        //padding 结束

        //加密后的密文
        szDataOut = new char[block_num*16+1];
        memset(szDataOut, 0, block_num*16+1);
        //加密字符串
        crijndael.Encrypt((char*)p_data, szDataOut, block_num*16);
        QString *result = new QString(QByteArray(szDataOut, block_num*16).toHex());

        delete[] p_data;
        p_data = NULL;
        delete[]  szDataOut;
        szDataOut = NULL;

        return result;
    }catch(QString){
        if(p_data != NULL){
            delete p_data;
        }
        if(szDataOut != NULL){
            delete szDataOut;
        }
        return NULL;
    }
}
