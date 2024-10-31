#ifndef KEYHELPER_H
#define KEYHELPER_H

#include <QString>

class KeyHelper
{
public:
    static KeyHelper *Instance();

public:
    QString GetClientId();
    bool CheckKeyVaild(QString _key);
    bool IsRegistered();

private:
    KeyHelper();

private:
    QString GetWMIC(const QString &cmd);
    QString GetCpuName();
    QString GetCpuId();
    QString GetDiskNum();
    QString GetXorEncrypt(const QString &data, char key);
    QString GetXorDecrypt(const QString data);

private:
    static KeyHelper *self;

    bool m_bRegistered;
};

#define KEYHELPER KeyHelper::Instance()

#endif // KEYHELPER_H
