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
#include <QDebug>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>

#include <QJsonObject>
#include <QJsonDocument>

#include "resizabledialog.h"
#include "userinfodialog.h"
#include "common.h"

class MainDialog : public ResizableDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

    void initUI();

    void onUserInfoClick();

private:

    void initAccount();
    void handleAccount();

    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    QSystemTrayIcon *system_tray;

    QStackedLayout *stackLayout;

};

#endif // MAINDIALOG_H
