#include "common.h"


QString CommonInfo::uuid=QString::null;
QString CommonInfo::skey=QString::null;
QString CommonInfo::wxsid=QString::null;
QString CommonInfo::wxuin=QString::null;
QString CommonInfo::ticket=QString::null;
QString CommonInfo::deviceId=QString::null;


QString CommonInfo::loginUrl="https://login.wx.qq.com/jslogin?appid=wx782c26e4c19acffb&lang=zh_CN&fun=new";
QString CommonInfo::qrCodeUrl="https://login.weixin.qq.com/qrcode/"+CommonInfo::uuid;
QString CommonInfo::initUrl="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxinit?lang=zh_CN&r=%1&pass_ticket=%2";
QString CommonInfo::contactUrl="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgetcontact?lang=zh_CN&seq=0&pass_ticket=%1&skey=%2&r=%3";

QNetworkAccessManager* CommonInfo::manager=NULL;

QString CommonInfo::getQRCodeUrl()
{
    return CommonInfo::qrCodeUrl+CommonInfo::uuid;
}

QString CommonInfo::getQRCodeUrl(QString uuid)
{
    return CommonInfo::qrCodeUrl+uuid;
}

QString CommonInfo::getScanResultUrl()
{
    return "https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?loginicon=true&uuid="+uuid;
}

QString CommonInfo::getInitUrl()
{
    return initUrl.arg(QDateTime::currentDateTime().toTime_t()).arg(ticket);
}

QString CommonInfo::getContactUrl()
{
    return contactUrl.arg(ticket).arg(skey).arg(QDateTime::currentDateTime().toTime_t());
}

QString CommonInfo::newDeviceId()
{
//    QString guid = QUuid::createUuid().toString();
//    guid.remove("{").remove("}").remove("-");
//    deviceId = "e"+ guid.left(15);
    return "e935472618632094";
}

QNetworkAccessManager *CommonInfo::getNetworkManager()
{
    if(manager==NULL)
    {
        manager = new QNetworkAccessManager();
    }
    return manager;
}
