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

    contactList = new QList<ContactInfo*>();
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

    toUserNameEdit = new QTextEdit();
    toUserNameEdit->setToolTip("To Who?");
    contentEdit = new QTextEdit();
    contentEdit->setToolTip("Content");
    QPushButton *sendBtn = new QPushButton("Send");
    connect(sendBtn,&QPushButton::clicked,this,&MainDialog::onSendMsgClick);

    rows->addWidget(toUserNameEdit);
    rows->addWidget(contentEdit);
    rows->addWidget(sendBtn);

//    stackLayout = new QStackedLayout();
//    stackLayout->addWidget(new QLabel("aaabbb"));
//    rows->addLayout(stackLayout,1);

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

void MainDialog::onSendMsgClick()
{
    QString toUserName = toUserNameEdit->toPlainText();
    QString content = contentEdit->toPlainText().append("  --from msg bot at %1").arg(Utils::getTimeStamp());

    sendMsg(toUserName,content);
}

void MainDialog::processContact(QJsonArray array)
{
    for(int i=0;i<array.size();i++)
    {
        ContactInfo *info = new ContactInfo();

        QJsonObject json = array.at(i).toObject();
        QJsonValue uin = json.value("Uin");
        if(uin!=QJsonValue::Undefined)
        {
            info->Uin = uin.toInt();
        }

        QJsonValue username = json.value("UserName");
        if(username!=QJsonValue::Undefined)
        {
            info->UserName = username.toString();
        }

        QJsonValue nickname = json.value("NickName");
        if(nickname!=QJsonValue::Undefined)
        {
            info->NickName = nickname.toString();
        }

        QJsonValue headimgurl = json.value("HeadImgUrl");
        if(headimgurl!=QJsonValue::Undefined)
        {
            info->HeadImgUrl = headimgurl.toString();
        }

        QJsonValue contactflag = json.value("ContactFlag");
        if(contactflag!=QJsonValue::Undefined)
        {
            info->ContactFlag = contactflag.toInt();
        }

        QJsonValue membercount = json.value("MemberCount");
        if(membercount!=QJsonValue::Undefined)
        {
            info->MemberCount = membercount.toInt();
        }

//        QJsonValue uin = json.value("MemberList");
//        if(uin!=QJsonValue::Undefined)
//        {
//            info->Uin = uin.toInt();
//        }

        QJsonValue remarkname = json.value("RemarkName");
        if(remarkname!=QJsonValue::Undefined)
        {
            info->RemarkName = remarkname.toInt();
        }

        QJsonValue hideinputbarflag = json.value("HideInputBarFlag");
        if(hideinputbarflag!=QJsonValue::Undefined)
        {
            info->HideInputBarFlag = hideinputbarflag.toInt();
        }

        QJsonValue sex = json.value("Sex");
        if(sex!=QJsonValue::Undefined)
        {
            info->Sex = sex.toInt();
        }

        QJsonValue signature = json.value("Signature");
        if(signature!=QJsonValue::Undefined)
        {
            info->Signature = signature.toString();
        }

        QJsonValue verifyflag = json.value("VerifyFlag");
        if(verifyflag!=QJsonValue::Undefined)
        {
            info->VerifyFlag = verifyflag.toInt();
        }

        QJsonValue owneruin = json.value("OwnerUin");
        if(owneruin!=QJsonValue::Undefined)
        {
            info->OwnerUin = owneruin.toInt();
        }

        QJsonValue pyinitial = json.value("PYInitial");
        if(pyinitial!=QJsonValue::Undefined)
        {
            info->PYInitial = pyinitial.toString();
        }

        QJsonValue pyquanpin = json.value("PYQuanPin");
        if(pyquanpin!=QJsonValue::Undefined)
        {
            info->PYQuanPin = pyquanpin.toString();
        }

        QJsonValue remarkpyinitial = json.value("RemarkPYInitial");
        if(remarkpyinitial!=QJsonValue::Undefined)
        {
            info->RemarkPYInitial = remarkpyinitial.toString();
        }

        QJsonValue remarkpyquanpin = json.value("RemarkPYQuanPin");
        if(remarkpyquanpin!=QJsonValue::Undefined)
        {
            info->RemarkPYQuanPin = remarkpyquanpin.toString();
        }

        QJsonValue starfriend = json.value("StarFriend");
        if(uin!=QJsonValue::Undefined)
        {
            info->StarFriend = starfriend.toInt();
        }

        QJsonValue appaccountflag = json.value("AppAccountFlag");
        if(appaccountflag!=QJsonValue::Undefined)
        {
            info->AppAccountFlag = appaccountflag.toInt();
        }

        QJsonValue statues = json.value("Statues");
        if(statues!=QJsonValue::Undefined)
        {
            info->Statues = statues.toInt();
        }

        QJsonValue attrstatus = json.value("AttrStatus");
        if(attrstatus!=QJsonValue::Undefined)
        {
            info->AttrStatus = attrstatus.toInt();
        }

        QJsonValue province = json.value("Province");
        if(province!=QJsonValue::Undefined)
        {
            info->Province = province.toString();
        }

        QJsonValue city = json.value("City");
        if(city!=QJsonValue::Undefined)
        {
            info->City = city.toString();
        }

        QJsonValue alias = json.value("Alias");
        if(alias!=QJsonValue::Undefined)
        {
            info->Alias = alias.toString();
        }

        QJsonValue snsflag = json.value("SnsFlag");
        if(snsflag!=QJsonValue::Undefined)
        {
            info->SnsFlag = snsflag.toInt();
        }

        QJsonValue unifriend = json.value("UniFriend");
        if(uin!=QJsonValue::Undefined)
        {
            info->StarFriend = unifriend.toInt();
        }

        QJsonValue displayname = json.value("DisplayName");
        if(displayname!=QJsonValue::Undefined)
        {
            info->DisplayName = displayname.toString();
        }

        QJsonValue chatroomid = json.value("ChatRoomId");
        if(chatroomid!=QJsonValue::Undefined)
        {
            info->ChatRoomId = chatroomid.toInt();
        }

        QJsonValue keyword = json.value("KeyWord");
        if(keyword!=QJsonValue::Undefined)
        {
            info->KeyWord = keyword.toString();
        }

        QJsonValue encrychatroomid = json.value("EncryChatRoomId");
        if(encrychatroomid!=QJsonValue::Undefined)
        {
            info->EncryChatRoomId = encrychatroomid.toString();
        }

        QJsonValue isowner = json.value("IsOwner");
        if(isowner!=QJsonValue::Undefined)
        {
            info->IsOwner = isowner.toInt();
        }
        qDebug()<<"add"<<info->UserName<<info->NickName<<info->Signature;
        contactList->append(info);
    }
}

void MainDialog::processSyncKey(QJsonArray array)
{
    syncKeyStr.clear();
    for(int i=0;i<array.size();i++)
    {
        QJsonObject json = array.at(i).toObject();
        QString val = QString("%1_%2|").arg(json.value("Key").toInt()).arg(json.value("Val").toInt());
        syncKeyStr.append(val);
    }
    syncKeyStr.chop(1);
    qDebug()<<"syncKey"<<syncKeyStr;
}

void MainDialog::processUser(QJsonObject json)
{
    user = new UserInfo();

    QJsonValue uin = json.value("Uin");
    if(uin!=QJsonValue::Undefined)
    {
        user->Uin = uin.toInt();
    }

    QJsonValue username = json.value("UserName");
    if(username!=QJsonValue::Undefined)
    {
        user->UserName = username.toString();
    }

    QJsonValue nickname = json.value("NickName");
    if(nickname!=QJsonValue::Undefined)
    {
        user->NickName = nickname.toString();
    }

    QJsonValue headimgurl = json.value("HeadImgUrl");
    if(headimgurl!=QJsonValue::Undefined)
    {
        user->HeadImgUrl = headimgurl.toString();
    }

    QJsonValue remarkname = json.value("RemarkName");
    if(remarkname!=QJsonValue::Undefined)
    {
        user->RemarkName = remarkname.toString();
    }

    QJsonValue pyinitial = json.value("PYInitial");
    if(pyinitial!=QJsonValue::Undefined)
    {
        user->PYInitial = pyinitial.toString();
    }

    QJsonValue pyquanpin = json.value("PYQuanPin");
    if(pyquanpin!=QJsonValue::Undefined)
    {
        user->PYQuanPin = pyquanpin.toString();
    }

    QJsonValue hideinputbarflag = json.value("HideInputBarFlag");
    if(hideinputbarflag!=QJsonValue::Undefined)
    {
        user->HideInputBarFlag = hideinputbarflag.toInt();
    }

    QJsonValue starfriend = json.value("StarFriend");
    if(starfriend!=QJsonValue::Undefined)
    {
        user->StarFriend = starfriend.toInt();
    }

    QJsonValue sex = json.value("Sex");
    if(sex!=QJsonValue::Undefined)
    {
        user->Sex = sex.toInt();
    }

    QJsonValue signature = json.value("Signature");
    if(signature!=QJsonValue::Undefined)
    {
        user->Signature = signature.toString();
    }

    QJsonValue appaccountflag = json.value("AppAccountFlag");
    if(appaccountflag!=QJsonValue::Undefined)
    {
        user->AppAccountFlag = appaccountflag.toInt();
    }

    QJsonValue verifyflag = json.value("VerifyFlag");
    if(verifyflag!=QJsonValue::Undefined)
    {
        user->VerifyFlag = verifyflag.toInt();
    }

    QJsonValue contactflag = json.value("ContactFlag");
    if(contactflag!=QJsonValue::Undefined)
    {
        user->ContactFlag = contactflag.toInt();
    }

    QJsonValue webwxpluginswitch = json.value("WebWxPluginSwitch");
    if(webwxpluginswitch!=QJsonValue::Undefined)
    {
        user->WebWxPluginSwitch = webwxpluginswitch.toInt();
    }

    QJsonValue headimgflag = json.value("HeadImgFlag");
    if(headimgflag!=QJsonValue::Undefined)
    {
        user->HeadImgFlag = headimgflag.toInt();
    }

    QJsonValue snsflag = json.value("SnsFlag");
    if(snsflag!=QJsonValue::Undefined)
    {
        user->SnsFlag = snsflag.toInt();
    }
}

void MainDialog::initAccount()
{
    QJsonObject data;
    data.insert("BaseRequest",Utils::getBaseRequest());

    QByteArray content = QJsonDocument(data).toJson(QJsonDocument::Compact);

    qDebug()<<CommonInfo::getInitUrl();
    qDebug()<<QString(content);

    reply = Utils::post(CommonInfo::getInitUrl(),content);
    connect(reply,&QNetworkReply::finished,this,&MainDialog::handleAccount);
}

void MainDialog::handleAccount()
{
    if(reply->error()==QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QString str = QTextCodec::codecForName("utf8")->toUnicode(response);

        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(response,&error);

        if(error.error==QJsonParseError::NoError)
        {
            if(document.isObject())
            {
                QJsonObject obj = document.object();
                QJsonObject baseResponse = obj.value("BaseResponse").toObject();
                if(baseResponse.value("Ret").toInt()==0)
                {
                    qDebug()<<"Init Success";
                    qDebug()<<"Start Process";
                    processContact(obj.value("ContactList").toArray());
                    processUser(obj.value("User").toObject());

                    syncKeyObj = obj.value("SyncKey").toObject();
                    processSyncKey(syncKeyObj.value("List").toArray());
                    qDebug()<<"Process Complate";
                }
                initContact();
                startSync();
            }
        }
        else
        {
            qDebug()<<"Response Decode Error:"<<error.errorString();
        }
    }
    else
    {
        qDebug()<<"handleAccount Error";
    }
}

void MainDialog::initContact()
{
    reply = Utils::get(CommonInfo::getContactUrl());
    connect(reply,&QNetworkReply::finished,this,&MainDialog::handleContact);
}

void MainDialog::handleContact()
{
    qDebug()<<"handleContact";
    QByteArray response = reply->readAll();
    QString str = QString(response);
    qDebug()<<str;
    QJsonParseError error;
    QJsonDocument document= QJsonDocument::fromJson(response,&error);
    if(error.error==QJsonParseError::NoError)
    {
        QJsonObject obj = document.object();
        QJsonObject baseResponse = obj.value("BaseResponse").toObject();
        if(baseResponse.value("Ret").toInt()==0)
        {
            processContact(obj.value("MemberList").toArray());
        }
    }
}

void MainDialog::sendMsg(QString toUserName,QString content)
{
    QJsonObject msg;
    msg.insert("ClientMsgId",Utils::getTimeStamp());
    msg.insert("Content",content);
    msg.insert("FromUserName",user->UserName);
    msg.insert("LocalID",Utils::getTimeStamp());
    msg.insert("ToUserName",toUserName);
    msg.insert("Type",1);

    QJsonObject data;
    data.insert("BaseRequest",Utils::getBaseRequest());
    data.insert("Msg",msg);
    data.insert("Scene",0);

    QByteArray bytes = QJsonDocument(data).toJson(QJsonDocument::Compact);

    qDebug()<<QString(bytes);
    reply = Utils::post(CommonInfo::getSendMsgUrl(),bytes);
    connect(reply,&QNetworkReply::finished,this,&MainDialog::handleSendResult);
}

void MainDialog::handleSendResult()
{
    QString str = QString(reply->readAll());
    qDebug()<<"handleSendResult"<<str;
    contentEdit->clear();
}

void MainDialog::startSync()
{
    timer = new QTimer();
    timer->setInterval(1000*60);
    connect(timer,&QTimer::timeout,this,&MainDialog::doSync);
    timer->start();
}

void MainDialog::stopSync()
{
    timer->stop();
}

void MainDialog::doSync()
{
    syncReply = Utils::get(CommonInfo::getSyncCheckUrl(syncKeyStr));
    connect(syncReply,&QNetworkReply::finished,this,&MainDialog::handleSync);
}

void MainDialog::handleSync()
{
    qDebug()<<"handleSync";
    QString str = QString(syncReply->readAll());
    qDebug()<<str;
    syncReply->deleteLater();
}

