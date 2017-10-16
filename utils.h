#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFile>
#include <QTextCodec>
#include <QByteArray>
#include <QDataStream>
#include <QPixmap>

class Utils
{
public:
    Utils();

    static QString loadStyleSheet(const QString &path);

    static void deleteFile(QString fileName);

    static void saveToFile(QByteArray bytes, QString fileName);

    static QPixmap base64ToImage(QByteArray bytes);
};

#endif // UTILS_H
