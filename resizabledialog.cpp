#include "resizabledialog.h"

ResizableDialog::ResizableDialog(QWidget *parent) : ClosableDialog(parent)
{
    btn_min = new QToolButton();
    btn_min->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    btn_min->setAutoRaise(true);
    btn_min->setCursor(Qt::PointingHandCursor);

    btn_max = new QToolButton();
    btn_max->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    btn_max->setAutoRaise(true);
    btn_max->setCursor(Qt::PointingHandCursor);

    connect(btn_min,&QToolButton::clicked,this,&ResizableDialog::onMinClick);
    connect(btn_max,&QToolButton::clicked,this,&ResizableDialog::onMaxClick);

    this->titleBar->insertWidget(1,btn_min);
    this->titleBar->insertWidget(2,btn_max);

    this->setMouseTracking(true);
}

void ResizableDialog::onMinClick()
{
    setWindowState(Qt::WindowMinimized);
}

void ResizableDialog::onMaxClick()
{
    if(this->windowState()==Qt::WindowMaximized)
    {
        setWindowState(Qt::WindowNoState);
        btn_max->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    }
    else
    {
        setWindowState(Qt::WindowMaximized);
        btn_max->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton));
    }
}

void ResizableDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftMousePressed)
    {
        int flag = calcFlag(rLastPos);
        setCursorType(flag);

        QPoint dPos = event->globalPos()-gLastPos;
        if(flag==22)
        {
            ClosableDialog::mouseMoveEvent(event);
        }
        else
        {
            QRect rect = geometry();
            switch(flag)
            {
            case 11:
                rect.setTopLeft(rect.topLeft()+dPos);
                break;
            case 13:
                rect.setTopRight(rect.topRight()+dPos);
                break;
            case 31:
                rect.setBottomLeft(rect.bottomLeft()+dPos);
                break;
            case 33:
                rect.setBottomRight(rect.bottomRight()+dPos);
                break;
            case 12:
                rect.setTop(rect.top()+dPos.y());
                break;
            case 21:
                rect.setLeft(rect.left()+dPos.x());
                break;
            case 23:
                rect.setRight(rect.right()+dPos.x());
                break;
            case 32:
                rect.setBottom(rect.bottom()+dPos.y());
                break;
            }
            setGeometry(rect);
        }
        rLastPos = event->pos();
        gLastPos = event->globalPos();
    }
    else
    {
        int flag = calcFlag(event->pos());
        setCursorType(flag);
        QDialog::mouseMoveEvent(event);
    }
}

int ResizableDialog::calcFlag(QPoint pos)
{
    int col= pos.y()<MARGIN?1:(pos.y()>this->height()-MARGIN?3:2);
    int row= pos.x()<MARGIN?1:(pos.x()>this->width()-MARGIN?3:2);

    return col*10+row;
}

void ResizableDialog::setCursorType(int flag)
{
    Qt::CursorShape cursor;
    switch(flag)
    {
    case 11:
    case 33:
        cursor = Qt::SizeFDiagCursor;
        break;
    case 13:
    case 31:
        cursor = Qt::SizeBDiagCursor;
        break;
    case 21:
    case 23:
        cursor = Qt::SizeHorCursor;
        break;
    case 12:
    case 32:
        cursor = Qt::SizeVerCursor;
        break;
    case 22:
        cursor = Qt::ArrowCursor;
        break;
    default:
        cursor = Qt::ArrowCursor;
        break;
    }
    setCursor(cursor);
}
