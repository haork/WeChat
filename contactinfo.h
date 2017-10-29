#ifndef CONTACTINFO_H
#define CONTACTINFO_H

#include <QObject>

class ContactInfo
{
public:
    ContactInfo();

    int Uin;
    /**
     * @brief UserName
     * @为用户名称
     * @@为群组名称
     */
    QString UserName;
    QString NickName;
    QString HeadImgUrl;
    /**
     * @brief ContactFlag
     * 1表示好友
     * 2表示群组
     * 3表示公众号
     */
    int ContactFlag;
    int MemberCount;
    QList<ContactInfo> MemberList;
    QString RemarkName;
    int HideInputBarFlag;
    /**
     * @brief Sex
     * 0表示未色环指
     * 1表示男
     * 2表示女
     */
    int Sex;
    /**
     * @brief Signature
     * 个性签名
     */
    QString Signature;
    int VerifyFlag;
    int OwnerUin;
    QString PYInitial;
    QString PYQuanPin;
    QString RemarkPYInitial;
    QString RemarkPYQuanPin;
    /**
     * @brief StarFriend
     * 是否星标好友
     * 0否
     * 1是
     */
    int StarFriend;
    int AppAccountFlag;
    int Statues;
    int AttrStatus;
    QString Province;
    QString City;
    QString Alias;
    int SnsFlag;
    int UniFriend;
    QString DisplayName;
    int ChatRoomId;
    QString KeyWord;
    QString EncryChatRoomId;
    int IsOwner;
};

#endif // CONTACTINFO_H
