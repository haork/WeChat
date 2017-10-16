#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContentWidget(QWidget *parent = 0);
    ~ContentWidget();

    void initUI();

    void onMinClick();
    void onMaxClick();
    void onCloseClick();

private:
    QPushButton *minBtn;
    QPushButton *maxBtn;
    QPushButton *closeBtn;
};

#endif // CONTENTWIDGET_H
