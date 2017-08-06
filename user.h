#ifndef USER_H
#define USER_H

#include <QObject>

class User
{
public:

    QString Uin;
    QString UserName;
    QString NickName;
    QString HeadImgUrl;
    QString PYInitial;
    QString PYQuanPin;
    QString RemarkPYInital;
    QString RemarkPYQuanPin;
    int HideInputBarFlag;
    int StarFriend;
    int Sex;
    QString Signature;
    int AppAccoutFlag;
    int VerifyFlag;
    int ContactFlag;
    int WebWxFpluginSwitch;
    int HeadImage;
    int SnsFlag;
};

#endif // USER_H
