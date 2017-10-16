#include "maindialog.h"
#include "utils.h"

MainDialog::MainDialog(QWidget *parent) :
    ResizableDialog(parent)
{
    initUI();
    system_tray = new QSystemTrayIcon();
    system_tray->setIcon(QIcon(":/images/Status_Bar_Remind_Icon.tiff"));
    system_tray->show();

    manager = CommonInfo::getNetworkManager();

    initAccount();
}

MainDialog::~MainDialog()
{
    system_tray->hide();
}

void MainDialog::initUI()
{
    Utils::loadStyleSheet("skin/common.qss");

    this->setObjectName("MainDialog");

    QPushButton *head = new QPushButton();
    head->setObjectName("headBtn");
    head->setCursor(Qt::PointingHandCursor);
    head->setIcon(QIcon(QPixmap(":/images/Expression_1.tiff")));


    QPushButton *btn1 = new QPushButton();
    btn1->setObjectName("chatBtn");
    btn1->setCheckable(true);
    btn1->setToolTip(tr("Chat"));
    btn1->setCursor(Qt::PointingHandCursor);

    QPushButton *btn2 = new QPushButton();
    btn2->setObjectName("contactBtn");
    btn2->setCheckable(true);
    btn2->setToolTip("Contact");
    btn2->setCursor(Qt::PointingHandCursor);

    QPushButton *btn3 = new QPushButton();
    btn3->setObjectName("favoriteBtn");
    btn3->setCheckable(true);
    btn3->setToolTip("Favorite");
    btn3->setCursor(Qt::PointingHandCursor);

    QButtonGroup *group = new QButtonGroup();
    group->addButton(btn1);
    group->addButton(btn2);
    group->addButton(btn3);

    QPushButton *btn4 = new QPushButton();
    btn4->setObjectName("settingBtn");
    btn4->setToolTip(tr("More"));
    btn4->setCursor(Qt::PointingHandCursor);
    connect(btn4,&QPushButton::clicked, this, &MainDialog::onUserInfoClick);


    QHBoxLayout *rows = new QHBoxLayout();

    QVBoxLayout *column = new QVBoxLayout();
    column->addWidget(head);
    column->addWidget(btn1);
    column->addWidget(btn2);
    column->addWidget(btn3);
    column->addStretch();
    column->addWidget(btn4);
    column->setSpacing(10);
    rows->addLayout(column,0);

    stackLayout = new QStackedLayout();
    stackLayout->addWidget(new QLabel("aaabbb"));
    rows->addLayout(stackLayout,1);

    layout->addLayout(rows,0,0,2,1);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setMargin(5);

    QLabel *label = new QLabel();
    label->setPixmap(QPixmap(":/images/Tabbar-Chat.tiff"));
    label->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(label);

    layout->addLayout(vLayout,1,1);
    layout->setRowStretch(1,1);
    layout->setColumnStretch(1,1);

}

void MainDialog::onUserInfoClick()
{
    UserInfoDialog *dialog = new UserInfoDialog();

    dialog->setGeometry(cursor().pos().x(), cursor().pos().y(), 100,100);
    dialog->show();
}

void MainDialog::initAccount()
{
    QJsonObject obj;
    obj.insert("Uin",CommonInfo::wxuin);
    obj.insert("Sid",CommonInfo::wxsid);
    obj.insert("Skey",CommonInfo::skey);
    obj.insert("DeviceID",CommonInfo::newDeviceId());

    QJsonObject data;
    data.insert("BaseRequest",obj);

    QByteArray content = QJsonDocument(data).toJson(QJsonDocument::Compact);

    qDebug()<<CommonInfo::getInitUrl();
    qDebug()<<QString(content);

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=utf-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader,content.length());
    request.setRawHeader("Host","wx.qq.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.3; WOW64; rv:56.0) Gecko/20100101 Firefox/56.0");
    request.setRawHeader("Accept","appliction/json, text/plain, */*");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3");
    request.setRawHeader("Accept-Encoding","gzip, deflate, br");
    request.setRawHeader("Referer","https://wx.qq.com/");

    request.setUrl(CommonInfo::getInitUrl());
    reply = manager->post(request,content);
    connect(reply,&QNetworkReply::finished,this,&MainDialog::handleAccount);
}

void MainDialog::handleAccount()
{
    qDebug()<<"handleAccount";
    if(reply->error()==QNetworkReply::NoError)
    {
        qDebug()<<manager->cookieJar()->cookiesForUrl(QUrl("https://qq.com"));

        QString str = QTextCodec::codecForName("utf8")->toUnicode(reply->readAll());
        qDebug()<<str;
    }
    else
    {
        qDebug()<<"handleAccount Error";
    }

    //pt2gguin=o0378996271; RK=fXvTBOn/aC; ptcz=a9ef5e4d7ae08d7b1eb8d3f7312115cdf838b1ba1bd701dcbca009d6be76bff0; pgv_pvid=8605981625; pgv_pvi=6817518592; webwxuvid=bb7ba3aac2c9d0131c74ef2e8d34261eb97bb9f1d8e9b04f7e42be901f0004fb; webwx_auth_ticket=CIsBEPu7+OALGmCnGsHpOp/BUQzmD/sB4YqGRj+Dv1LvSwYGqObNWYDPgm9XmWhbggkMbsoff5NWtYYUgLx3KZGRL1tuWaSuI10MI01AfqY/nzPY3q91ZwP0vw8G9397YI2hH/5zlqrF80k=; o_cookie=378996271; tvfe_boss_uuid=036e13a7ef0467ef; pac_uid=1_378996271; mobileUV=1_15e70c8a7fd_6303a; wxuin=5763215; wxloadtime=1507994302; mm_lang=zh_CN; wxpluginkey=1507969663; login_frequency=1; last_wxuin=5763215; uin=o0378996271; skey=@EPONbjyI4; pgv_info=ssid=s8006026972; wxsid=jDlXbhDlA+aomiaY; webwx_data_ticket=gScZICkITF5EUTNAsBjvIDUu; MM_WX_NOTIFY_STATE=1; MM_WX_SOUND_STATE=1
}

