#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent):ClosableDialog(parent)
{
    initUI();

    stack->setCurrentIndex(0);

    manager = CommonInfo::getNetworkManager();

    getUUID();
}

void LoginDialog::getUUID()
{
    QString url = CommonInfo::getLoginUrl();
    qDebug()<<url;
    reply = manager->get(QNetworkRequest(url));
    connect(reply,&QNetworkReply::finished,this,&LoginDialog::handleUUID);
}

void LoginDialog::handleUUID()
{
    QString str = QTextCodec::codecForName("utf8")->toUnicode(reply->readAll());
    QStringList list = str.split("\"",QString::SkipEmptyParts);
    if(list.size()>1)
    {
        CommonInfo::uuid = list.at(1);

        qDebug()<<CommonInfo::uuid;

        getQRCode();
    }
}

void LoginDialog::getQRCode()
{
    qDebug()<<CommonInfo::getQRCodeUrl();

    Utils::deleteFile("qrcode.jpg");

    reply = manager->get(QNetworkRequest(CommonInfo::getQRCodeUrl()));
    connect(reply,&QNetworkReply::finished,this,&LoginDialog::handleQRCode);
}

void LoginDialog::handleQRCode()
{
    Utils::saveToFile(reply->readAll(),"qrcode.jpg");

    QPixmap pixmap;
    if(pixmap.load("qrcode.jpg"))
    {
        qrCode->setPixmap(pixmap);
        waitForScan(1);
    }
}

void LoginDialog::waitForScan(int tip)
{
    QString url = CommonInfo::getScanResultUrl(tip);
    qDebug()<<url;
    reply = manager->get(QNetworkRequest(url));
    connect(reply,&QNetworkReply::finished,this,&LoginDialog::handleScan);
}

/**
 * @brief LoginDialog::handleScan
 * 408 登陆超时
 * 201 扫描成功
 * 200 确认登录
 */
void LoginDialog::handleScan()
{
    QString str = QTextCodec::codecForName("utf8")->toUnicode(reply->readAll());
    //qDebug()<<str;
    QStringList list = str.split(";",QString::SkipEmptyParts);

    if(list.size()>=2)
    {
        QString codeStr = ((QString)list.at(0)).split("=").at(1);
        switch(codeStr.toInt())
        {
        case 200:
            {
                QString url = ((QString)list.at(1)).split("\"").at(1);
                qDebug()<<url;
                getCookie(url+"&fun=new&version=v2");
            }
            break;
        case 201:
            {


                QString userAvatar = ((QString)list.at(2)).split("'").at(0);
                QString subStr = userAvatar.mid(7);
                QPixmap avatar = Utils::base64ToImage(subStr.toLocal8Bit());
                avatar.save("avatar.jpg");
                qrCode->setPixmap(avatar);
                waitForScan(0);
            }
            break;
        case 408:
            {
                qDebug()<<"登录超时";
                waitForScan(1);
            }
            break;
        default:
            break;
        }
    }

}

void LoginDialog::getCookie(QString url)
{
    qDebug()<<"getCookie at:"+url;
    reply = manager->get(QNetworkRequest(url));
    connect(reply,&QNetworkReply::finished,this,&LoginDialog::handleCookie);
}

void LoginDialog::handleCookie()
{
    qDebug()<<manager->cookieJar()->cookiesForUrl(QUrl("https://wx.qq.com"));

    QString str = QTextCodec::codecForName("utf8")->toUnicode(reply->readAll());

    QDomDocument doc;
    if(doc.setContent(str))
    {
        if(!doc.isNull())
        {
            QDomElement root = doc.documentElement();
            QDomNodeList list = root.childNodes();
            for(int i=0;i<list.count();i++)
            {
                QDomElement elem = list.at(i).toElement();
                if(elem.tagName()=="ret")
                {
                    qDebug()<<"Ret"<<elem.text();
                }
                else if(elem.tagName()=="message")
                {
                    qDebug()<<"Message"<<elem.text();
                }
                else if(elem.tagName()=="skey")
                {
                    CommonInfo::skey=elem.text();
                }
                else if(elem.tagName()=="wxsid")
                {
                    CommonInfo::wxsid=elem.text();
                }
                else if(elem.tagName()=="wxuin")
                {
                    CommonInfo::wxuin=elem.text();
                }
                else if(elem.tagName()=="pass_ticket")
                {
                    CommonInfo::ticket=elem.text().replace("%3D","");
                }
            }
            MainDialog *dialog = new MainDialog();
            dialog->show();
            this->close();
        }
    }
}

QWidget *LoginDialog::initPage1()
{
    qrCode = new QLabel();
    qrCode->setMaximumWidth(188);
    qrCode->setMaximumHeight(188);
    qrCode->setScaledContents(true);
    qrCode->setAlignment(Qt::AlignCenter);

    notice = new QLabel();
    notice->setText(QStringLiteral("使用微信扫一扫以登录"));
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(qrCode);
    vLayout->addWidget(notice);
    vLayout->setSpacing(20);

    vLayout->setAlignment(qrCode,Qt::AlignHCenter);
    vLayout->setAlignment(notice,Qt::AlignHCenter);

    QWidget *widget = new QWidget();
    widget->setLayout(vLayout);
    return widget;
}

QWidget *LoginDialog::initPage2()
{

    image = new QLabel();
    image->setScaledContents(true);
    image->setCursor(QCursor(Qt::PointingHandCursor));
    image->setMaximumWidth(92);
    image->setMaximumHeight(92);

    name = new QLabel();
    name->setText(QStringLiteral("小凯"));

    loginBtn = new QPushButton(QStringLiteral("登录"));
    loginBtn->setMinimumWidth(210);
    loginBtn->setMinimumHeight(40);
    loginBtn->setCursor(QCursor(Qt::PointingHandCursor));

    switchBtn = new QCommandLinkButton();
    switchBtn->setText(QStringLiteral("切换账号"));
    switchBtn->setCursor(QCursor(Qt::PointingHandCursor));

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(image);
    vLayout->addWidget(name);
    vLayout->addWidget(loginBtn);
    vLayout->addWidget(switchBtn);
    vLayout->setSpacing(20);

    vLayout->setAlignment(image,Qt::AlignHCenter);
    vLayout->setAlignment(name,Qt::AlignHCenter);
    vLayout->setAlignment(loginBtn,Qt::AlignHCenter);
    vLayout->setAlignment(switchBtn,Qt::AlignHCenter);

    QWidget *widget = new QWidget();
    widget->setLayout(vLayout);
    return widget;
}

void LoginDialog::initUI()
{
    btn_setting = new QToolButton();
    btn_setting->setIcon(style()->standardIcon(QStyle::SP_TitleBarMenuButton));
    btn_setting->setAutoRaise(true);
    btn_setting->setCursor(Qt::PointingHandCursor);

    this->titleBar->insertWidget(1,btn_setting);

    QString styleSheet = Utils::loadStyleSheet("skin/login.qss");

    resize(280,400);
    setStyleSheet(styleSheet);

    title=new QLabel();
    title->setText(QStringLiteral("微信"));
    title->setAlignment(Qt::AlignCenter);
    title->setMinimumWidth(80);
    title->setMinimumHeight(50);

    stack = new QStackedLayout();
    QWidget *page1 = initPage1();
    QWidget *page2 = initPage2();
    stack->addWidget(page1);
    stack->addWidget(page2);
    stack->setAlignment(page1,Qt::AlignCenter);
    stack->setAlignment(page2,Qt::AlignCenter);

    layout->addWidget(title,0,0,2,1);
    layout->addLayout(stack,2,0,1,2);

    layout->setRowStretch(0,0);
    layout->setRowStretch(1,0);
    layout->setRowStretch(2,1);
    layout->setAlignment(stack,Qt::AlignCenter);
}

