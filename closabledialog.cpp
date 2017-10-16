#include "closabledialog.h"

ClosableDialog::ClosableDialog(QWidget *parent) : BaseDialog(parent)
{
    setStyleSheet(Utils::loadStyleSheet("skin/common.qss"));

    btn_close = new QToolButton();
    btn_close->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    btn_close->setAutoRaise(true);
    btn_close->setCursor(Qt::PointingHandCursor);

    titleBar = new QHBoxLayout();
    titleBar->addStretch();
    titleBar->addWidget(btn_close);
    titleBar->setMargin(0);
    titleBar->setSpacing(0);

    layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addLayout(titleBar,0,1,Qt::AlignTop);

    layout->setRowStretch(0,0);

    connect(btn_close,&QToolButton::clicked,this,&ClosableDialog::close);
}


void ClosableDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftMousePressed)
    {
        this->move(event->globalPos()-gLastPos+pos());

        gLastPos = event->globalPos();
        event->ignore();
    }
}

void ClosableDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        isLeftMousePressed = true;
        rLastPos = event->pos();
        gLastPos = event->globalPos();
        event->ignore();
    }
}

void ClosableDialog::mouseReleaseEvent(QMouseEvent *event)
{
    isLeftMousePressed = false;
    event->ignore();
}
