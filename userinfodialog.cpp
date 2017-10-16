#include "userinfodialog.h"

UserInfoDialog::UserInfoDialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);
    initUI();
}

void UserInfoDialog::initUI()
{
    name = new QLabel();
    image = new QLabel();
    wxnumber = new QLabel();
    area = new QLabel();

    sendCardBtn = new QPushButton();
    sendMsgBtn = new QPushButton();

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(name,0,0);
    layout->addWidget(new QLabel(tr("wxnumber")),1,0);
    layout->addWidget(image,0,1,2,2);
    layout->addWidget(wxnumber,2,0);
    layout->addWidget(area,3,0);
    layout->addWidget(sendCardBtn,4,2);
    layout->addWidget(sendMsgBtn,4,3);
}

