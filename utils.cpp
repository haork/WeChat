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

long Utils::getTimeStamp()
{
    return QDateTime().currentDateTime().toTime_t(); //QTime::currentTime().secsTo(QTime(1970,1,1));
}

QNetworkReply *Utils::post(QString url,QByteArray content)
{
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setAttribute(QNetworkRequest::ConnectionEncryptedAttribute,true);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=UTF-8");
    if(!content.isNull())
    {
        request.setHeader(QNetworkRequest::ContentLengthHeader,content.length());
    }
    request.setRawHeader("Host","wx.qq.com");
    request.setRawHeader("Pragma","no-cache");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Referer","https://wx.qq.com/?&lang=zh_CN");

    return CommonInfo::getNetworkManager()->post(request,content);
}

QNetworkReply *Utils::get(QString url)
{
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setAttribute(QNetworkRequest::ConnectionEncryptedAttribute,true);
    request.setRawHeader("Host","wx.qq.com");
    request.setRawHeader("Pragma","no-cache");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Referer","https://wx.qq.com/?&lang=zh_CN");
    return CommonInfo::getNetworkManager()->get(request);
}

QJsonObject Utils::getBaseRequest()
{
    QJsonObject obj;
    obj.insert("Uin",CommonInfo::wxuin);
    obj.insert("Sid",CommonInfo::wxsid);
    obj.insert("Skey",CommonInfo::skey);
    obj.insert("DeviceID",CommonInfo::newDeviceId());
    return obj;
}
