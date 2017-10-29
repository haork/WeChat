#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFile>
#include <QTextCodec>
#include <QByteArray>
#include <QDataStream>
#include <QPixmap>
#include <QTime>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonObject>

#include "common.h"

class Utils
{
public:
    Utils();

    static QString loadStyleSheet(const QString &path);

    static void deleteFile(QString fileName);

    static void saveToFile(QByteArray bytes, QString fileName);

    static QPixmap base64ToImage(QByteArray bytes);

    static long getTimeStamp();

    static QNetworkReply *post(QString url,QByteArray content=NULL);

    static QNetworkReply *get(QString url);

    static QJsonObject getBaseRequest();
};

#endif // UTILS_H
