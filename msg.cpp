#include "msg.h"


QJsonObject Msg::toJsonObject()
{
    QJsonObject obj;
    obj.insert("Type",Type);
    obj.insert("Content",Content);
    obj.insert("FromUserName",FromUserName);
    obj.insert("ToUserName",ToUserName);
    obj.insert("LocalID",LocalID);
    obj.insert("ClientMsgId",ClientMsgId);
    return obj;
}
