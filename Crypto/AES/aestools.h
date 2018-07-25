#ifndef AESTOOLS_H
#define AESTOOLS_H
#include <QByteArray>

#include "Rijndael.h"

/**
 *该类实现加密解密
 */
class AESTools
{
private:
    CRijndael crijndael;
public:
    /**
     * @brief AESTools
     * @param key
     * 如果密匙长度不是16，自动纠正
     */
    AESTools(QByteArray key);

    /**
     * @brief Encrypt
     * @param data
     * @return
     * 将UTF-8字符串加密成HEX串
     */
    QString* Encrypt(QString const* data);

    /**
     * @brief Decrypt
     * @param hexData
     * @return
     * 将HEX串解密为UTF-8字符串
     */
    QByteArray Decrypt(QByteArray const data);
};

#endif // AESTOOLS_H
