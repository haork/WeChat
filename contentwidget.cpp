#include "contentwidget.h"


ContentWidget::ContentWidget(QWidget *parent) :
    QWidget(parent)
{
    initUI();
}



ContentWidget::~ContentWidget()
{

}

void ContentWidget::initUI()
{
    setObjectName("ContentWidget");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *head = new QHBoxLayout();


    minBtn = new QPushButton("Min");
    maxBtn = new QPushButton("Max");
    closeBtn = new QPushButton("Close");

    head->addStretch();
    head->addWidget(minBtn);
    head->addWidget(maxBtn);
    head->addWidget(closeBtn);

    layout->addLayout(head,0);
    layout->setAlignment(head,Qt::AlignTop);

    setStyleSheet("background:rgb(245,245,245)");

}

void ContentWidget::onMinClick()
{

}

void ContentWidget::onMaxClick()
{

}

void ContentWidget::onCloseClick()
{
    this->close();
}
