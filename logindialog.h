#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QCommandLinkButton>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QDebug>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>


#include <QDomDocument>


#include "common.h"
#include "closabledialog.h"
#include "maindialog.h"

class LoginDialog : public ClosableDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget *parent=0);
    void initUI();

    void getUUID();
    void handleUUID();

    void getQRCode();
    void handleQRCode();

    void waitForScan();
    void handleScan();

    void getCookie(QString url);
    void handleCookie();

private:

    QWidget *initPage1();
    QWidget *initPage2();

    QLabel *title;

    QStackedLayout *stack;

    //page1
    QLabel *qrCode;
    QLabel *notice;

    //page2
    QLabel *image;
    QLabel *name;
    QToolButton *btn_setting;

    QPushButton *loginBtn;
    QCommandLinkButton *switchBtn;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
};

#endif // LOGINDIALOG_H
