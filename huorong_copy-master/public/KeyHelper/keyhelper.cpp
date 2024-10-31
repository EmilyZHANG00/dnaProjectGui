#include "keyhelper.h"
#include <QProcess>
#include <QByteArray>
#include <QDebug>
#include <QMutex>
#include <QCryptographicHash>

#define KEY_MASK 107
#define KEY_STR_MASK  "D&SVvgbkaGUys^pH"

KeyHelper *KeyHelper::self = 0;
KeyHelper::KeyHelper()
{
    m_bRegistered = false;
}

KeyHelper *KeyHelper::Instance()
{
    if (!self) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!self) {
            self = new KeyHelper;
        }
    }

    return self;
}

QString KeyHelper::GetClientId()
{
    QString key = QString("%1|%2|%3").arg(GetCpuName()).arg(GetCpuId()).arg(GetDiskNum());
    QString base64 = GetXorEncrypt(key, (char)KEY_MASK);
    return base64;
}

bool KeyHelper::CheckKeyVaild(QString _key)
{
    QString key = QString("%1|%2|%3").arg(GetCpuName()).arg(GetCpuId()).arg(GetDiskNum());
    m_bRegistered = (_key == GetXorDecrypt(GetXorEncrypt(key, (char)KEY_MASK)));
    return m_bRegistered;
}

bool KeyHelper::IsRegistered()
{
#ifndef NEED_REGISTERED_MECHANISM
    return true;
#endif
    return m_bRegistered;
}

QString KeyHelper::GetWMIC(const QString &cmd)
{
    //获取cpu名称：wmic cpu get Name
    //获取cpu核心数：wmic cpu get NumberOfCores
    //获取cpu线程数：wmic cpu get NumberOfLogicalProcessors
    //查询cpu序列号：wmic cpu get processorid
    //查询主板序列号：wmic baseboard get serialnumber
    //查询BIOS序列号：wmic bios get serialnumber
    //查看硬盘：wmic diskdrive get serialnumber
    QProcess p;
    p.start(cmd);
    p.waitForFinished();
    QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
    QStringList list = cmd.split(" ");
    result = result.remove(list.last(), Qt::CaseInsensitive);
    result = result.replace("\r", "");
    result = result.replace("\n", "");
    result = result.simplified();
    return result;
}

QString KeyHelper::GetCpuName()
{
    return GetWMIC("wmic cpu get name");
}

QString KeyHelper::GetCpuId()
{
    return GetWMIC("wmic cpu get processorid");
}

QString KeyHelper::GetDiskNum()
{
    return GetWMIC("wmic diskdrive where index=0 get serialnumber");
}

QString KeyHelper::GetXorEncrypt(const QString &data, char key)
{
    //采用异或加密,也可以自行更改算法
    QByteArray buffer = data.toLatin1();
    int size = buffer.size();
    for (int i = 0; i < size; i++) {
        buffer[i] = buffer.at(i) ^ key;
    }

    QByteArray md5 = QCryptographicHash::hash(buffer, QCryptographicHash::Md5);
    return md5.toHex();
}

QString KeyHelper::GetXorDecrypt(const QString data)
{
    QByteArray md5 = QCryptographicHash::hash(QString(data + KEY_STR_MASK).toLatin1(), QCryptographicHash::Md5);
    return md5.toHex();
}
