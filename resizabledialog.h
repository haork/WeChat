#ifndef RESIZABLEDIALOG_H
#define RESIZABLEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QToolButton>

#include "closabledialog.h"

class ResizableDialog : public ClosableDialog
{
    Q_OBJECT

public:
    ResizableDialog(QWidget *parent=0);

protected:
    void mouseMoveEvent(QMouseEvent *event);

    void onMinClick();
    void onMaxClick();

private:
    int MARGIN = 5;

    int calcFlag(QPoint pos);
    void setCursorType(int flag);

    QToolButton *btn_min;
    QToolButton *btn_max;

};

#endif // RESIZABLEDIALOG_H
