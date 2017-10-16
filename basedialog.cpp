#include "basedialog.h"
#include "utils.h"

BaseDialog::BaseDialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);

    setStyleSheet(Utils::loadStyleSheet("skin/common.qss"));

}

