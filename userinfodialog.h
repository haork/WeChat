#ifndef USERINFODIALOG_H
#define USERINFODIALOG_H

#include "basedialog.h"
#include <QGridLayout>
#include <QGraphicsLineItem>
#include <QLabel>
#include <QPushButton>

class UserInfoDialog : public QDialog
{
public:
    UserInfoDialog(QWidget *parent=0);

    void initUI();

private:
    QLabel *name;
    QLabel *image;
    QLabel *wxnumber;
    QLabel *area;

    QPushButton *sendCardBtn;
    QPushButton *sendMsgBtn;
};

#endif // USERINFODIALOG_H
