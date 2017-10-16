#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMouseEvent>
#include <QToolButton>
#include <QStyle>

class BaseDialog : public QDialog
{
    Q_OBJECT
public:
    BaseDialog(QWidget *parent = 0);

};

#endif // BASEDIALOG_H
