#ifndef COMMONINFO_H
#define COMMONINFO_H

#include <QObject>
#include <QString>
#include <QUuid>
#include <QDateTime>
#include <QNetworkAccessManager>

class CommonInfo
{

public:
    static QString loginUrl;
    static QString qrCodeUrl;
    static QString initUrl;
    static QString contactUrl;

    static QString uuid;
    static QString skey;
    static QString wxsid;
    static QString wxuin;
    static QString ticket;
    static QString deviceId;

    static QString getQRCodeUrl();
    static QString getQRCodeUrl(QString uuid);

    static QString getScanResultUrl();

    static QString getInitUrl();

    static QString getContactUrl();

    static QString newDeviceId();

    static QNetworkAccessManager *getNetworkManager();

private:

    static QNetworkAccessManager *manager;
};

#endif // COMMONINFO_H
