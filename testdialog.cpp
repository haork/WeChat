#include "testdialog.h"

TestDialog::TestDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *btn1 = new QPushButton(tr("btn1"));
    connect(btn1,&QPushButton::clicked,this,&TestDialog::onBtn1Click);

    QPushButton *btn2 = new QPushButton(tr("btn2"));
    connect(btn2,&QPushButton::clicked,this,&TestDialog::onBtn2Click);

    layout->addWidget(btn1);
    layout->addWidget(btn2);

    manager = new QNetworkAccessManager();
}

void TestDialog::onBtn1Click()
{
    reply = manager->get(QNetworkRequest(tr("http://localhost:8080/lanyuanweb/api/nest?interfaceCode=API_NEST_LOGIN&username=app&password=123456789")));
    connect(reply,&QNetworkReply::finished,this,&TestDialog::onResponse);
}

void TestDialog::onBtn2Click()
{
    QJsonObject obj;
    obj.insert("code","200");
    obj.insert("message",QStringLiteral("操作成功"));
    obj.insert("Sid","aefasdfasdf");

    QJsonObject data;
    data.insert("BaseRequest",obj);

    QByteArray content = QJsonDocument(data).toJson(QJsonDocument::Compact);

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=utf-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader,content.length());
    request.setUrl(tr("http://localhost:8080/lanyuanweb/api/nest/test"));

    reply = manager->post(request,content);
    connect(reply,&QNetworkReply::finished,this,&TestDialog::onResponse);
}

void TestDialog::onResponse()
{
    qDebug()<<QString(reply->readAll());
}
