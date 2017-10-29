#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include "resizabledialog.h"

class TestDialog : public QDialog
{
public:
    TestDialog(QWidget *parent=0);

    void onBtn1Click();

    void onBtn2Click();

    void onResponse();

private:

    QNetworkAccessManager *manager;
    QNetworkReply *reply;

};

#endif // TESTDIALOG_H
