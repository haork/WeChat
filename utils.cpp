#include "utils.h"

Utils::Utils()
{

}

QString Utils::loadStyleSheet(const QString &path)
{
    QFile file(path);
    if(file.exists())
    {
        file.open(QFile::ReadOnly);
        return QTextCodec::codecForName("utf8")->toUnicode(file.readAll());
    }
    else
    {
        return QString::null;
    }
}

void Utils::deleteFile(QString fileName)
{
    QFile file(fileName);
    if(file.exists())
    {
        file.remove();
    }
}

void Utils::saveToFile(QByteArray bytes, QString fileName)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly|QFile::Append);
    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.writeRawData(bytes.constData(), bytes.count());
    file.close();
}

QPixmap Utils::base64ToImage(QByteArray bytes)
{
    QByteArray data =QByteArray::fromBase64(bytes);
    QPixmap image;
    image.loadFromData(data);
    return image;
}
