#ifndef MSG_H
#define MSG_H

#include <QObject>
#include <QJsonObject>

class Msg
{
public:
    int Type=0;
    QString Content;
    QString FromUserName;
    QString ToUserName;
    QString LocalID;
    QString ClientMsgId;

    QJsonObject toJsonObject();
};

#endif // MSG_H
