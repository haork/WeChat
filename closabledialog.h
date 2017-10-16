#ifndef CLOSABLEDIALOG_H
#define CLOSABLEDIALOG_H

#include <QObject>
#include <QDialog>

#include "basedialog.h"
#include "utils.h"


class ClosableDialog : public BaseDialog
{
    Q_OBJECT
public:
    ClosableDialog(QWidget *parent);

protected:
    bool isLeftMousePressed=false;
    QPoint rLastPos;
    QPoint gLastPos;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    QHBoxLayout *titleBar;
    QGridLayout *layout;

private:

    QToolButton *btn_close;
};

#endif // CLOSABLEDIALOG_H
