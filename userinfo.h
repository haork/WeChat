#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

class UserInfo
{
public:
    UserInfo();

    int Uin;
    QString UserName;
    QString NickName;
    QString HeadImgUrl;
    QString RemarkName;
    QString PYInitial;
    QString PYQuanPin;
    QString RemarkPYInital;
    QString RemarkPYQuanPin;
    int HideInputBarFlag;
    int StarFriend;
    int Sex;
    QString Signature;
    int AppAccountFlag;
    int VerifyFlag;
    int ContactFlag;
    int WebWxPluginSwitch;
    int HeadImgFlag;
    int SnsFlag;
};

#endif // USERINFO_H
