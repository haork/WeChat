#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QListWidget>
#include <QTabBar>
#include <QTabWidget>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QStackedLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QTimer>
#include <QTextEdit>
#include <QDebug>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "resizabledialog.h"
#include "userinfodialog.h"
#include "common.h"
#include "models.h"

class MainDialog : public ResizableDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

    void initUI();

    void onUserInfoClick();

    void onSendMsgClick();

    void processContact(QJsonArray array);

    void processSyncKey(QJsonArray array);

    void processUser(QJsonObject json);

private:

    void initAccount();
    void handleAccount();

    void initContact();
    void handleContact();

    void sendMsg(QString toUserName,QString content);
    void handleSendResult();

    void startSync();
    void stopSync();
    void doSync();
    void handleSync();

    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkReply *syncReply;

    QSystemTrayIcon *system_tray;

    QStackedLayout *stackLayout;

    UserInfo *user;
    QList<ContactInfo*> *contactList;
    QJsonObject syncKeyObj;
    QString syncKeyStr;

    QTimer *timer;


    QTextEdit *toUserNameEdit;
    QTextEdit *contentEdit;
};

#endif // MAINDIALOG_H
