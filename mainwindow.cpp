#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QDebug>
#include <msg.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Msg msg;
    msg.FromUserName="123";
    msg.ToUserName="234";


    QJsonDocument document;
    document.setObject(msg.toJsonObject());
    QByteArray array = document.toJson(QJsonDocument::Compact);
    QString json(array);
    qDebug()<<json;
}

MainWindow::~MainWindow()
{
    delete ui;
}
