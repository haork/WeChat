#include "common.h"

QString CommonInfo::appid="wx782c26e4c19acffb";
QString CommonInfo::uuid=QString::null;
QString CommonInfo::skey=QString::null;
QString CommonInfo::wxsid=QString::null;
QString CommonInfo::wxuin=QString::null;
QString CommonInfo::ticket=QString::null;
QString CommonInfo::deviceId=QString::null;



QString CommonInfo::loginUrl="https://login.wx.qq.com/jslogin?appid=wx782c26e4c19acffb&lang=zh_CN&fun=new&redirect_uri=https%3A%2F%2Fwx.qq.com%2Fcgi-bin%2Fmmwebwx-bin%2Fwebwxnewloginpage";
QString CommonInfo::qrCodeUrl="https://login.weixin.qq.com/qrcode/%1";
QString CommonInfo::scanResultUrl="https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?loginicon=true&uuid=%1&tip=%2&r=%3&_=%4";
QString CommonInfo::initUrl="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxinit?lang=zh_CN&r=%1&pass_ticket=%2";
QString CommonInfo::contactUrl="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgetcontact?lang=zh_CN&seq=0&pass_ticket=%1&skey=%2&r=%3";
QString CommonInfo::statusnotifyUrl="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxstatusnotify?lang=zh_CN";
QString CommonInfo::synccheckUrl="https://webpush.wx2.qq.com/cgi-bin/mmwebwx-bin/synccheck?sid=%1&uin=%2&skey=%3&deviceid=%4&synckey=%5&r=%6";
QString CommonInfo::newMsgUrl="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxsync?lang=zh_CN&sid=%1&skey=%2&pass_ticket=%3";
QString CommonInfo::sendMsgUrl="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxsendmsg?lang=zh_CN&pass_ticket=%1";
QString CommonInfo::logoutUrl="https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxlogout";


QNetworkAccessManager* CommonInfo::manager=NULL;

QString CommonInfo::getLoginUrl()
{
    return loginUrl;
}

QString CommonInfo::getQRCodeUrl()
{
    return qrCodeUrl.arg(uuid);
}

QString CommonInfo::getQRCodeUrl(QString uuid)
{
    return qrCodeUrl.arg(uuid);
}

QString CommonInfo::getScanResultUrl(int tip)
{
    return scanResultUrl.arg(uuid).arg(tip).arg(~(Utils::getTimeStamp())).arg(Utils::getTimeStamp());
}

QString CommonInfo::getInitUrl()
{
    return initUrl.arg(~(Utils::getTimeStamp())).arg(ticket);
}

QString CommonInfo::getContactUrl()
{
    return contactUrl.arg(ticket).arg(skey).arg(Utils::getTimeStamp());
}


QString CommonInfo::newDeviceId()
{
//    QString guid = QUuid::createUuid().toString();
//    guid.remove("{").remove("}").remove("-");
//    deviceId = "e"+ guid.left(15);

    QByteArray array;
    array.append("e");
    for(int i=0;i<15;i++)
    {
        array.append('0'+qrand()%10);
    }
    return QString(array);
}

QString CommonInfo::getSyncCheckUrl(QString synckey)
{
    return synccheckUrl.arg(wxsid).arg(wxuin).arg(skey).arg(newDeviceId()).arg(synckey).arg(Utils::getTimeStamp());
}

QString CommonInfo::getNewMsgUrl()
{
    return newMsgUrl.arg(wxsid).arg(skey).arg(ticket);
}

QString CommonInfo::getSendMsgUrl()
{
    return sendMsgUrl.arg(ticket);
}

QNetworkAccessManager *CommonInfo::getNetworkManager()
{
    if(manager==NULL)
    {
        qDebug()<<"init network manager";
        //cookieJar = new QNetworkCookieJar();
        manager = new QNetworkAccessManager();
        //manager->setCookieJar(cookieJar);
    }
    return manager;
}
