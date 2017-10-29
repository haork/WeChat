#ifndef COMMONINFO_H
#define COMMONINFO_H

#include <QObject>
#include <QString>
#include <QUuid>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QtMath>

#include "utils.h"

class CommonInfo
{
public:

    static QString loginUrl;
    static QString qrCodeUrl;
    static QString scanResultUrl;
    static QString initUrl;
    static QString contactUrl;
    static QString sendMsgUrl;
    static QString statusnotifyUrl;
    static QString newMsgUrl;

    static QString synccheckUrl;

    static QString logoutUrl;

    static QString appid;
    static QString uuid;
    static QString skey;
    static QString wxsid;
    static QString wxuin;
    static QString ticket;
    static QString deviceId;

    static QString getLoginUrl();

    static QString getQRCodeUrl();

    static QString getQRCodeUrl(QString uuid);

    static QString getScanResultUrl(int tip);

    static QString getInitUrl();

    static QString getContactUrl();

    static QString getSyncCheckUrl(QString synckey);

    static QString getNewMsgUrl();

    static QString getSendMsgUrl();

    static QString newDeviceId();

    static QNetworkAccessManager *getNetworkManager();

private:

    static QNetworkAccessManager *manager;
    static QNetworkCookieJar *cookieJar;
};

#endif // COMMONINFO_H
