#include <QApplication>
#include <QTextCodec>
#include "logindialog.h"
#include "maindialog.h"
#include "basedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

//    union ppt{
//             int a;
//            unsigned char b[2];
//        }dl;
//        dl.a=0xff00;
//        if(dl.b[0]==0xff)
//        {
//            qDebug()<<"This is bigterm!";
//        }
//        else{
//            qDebug()<<"This is littleterm!";
//        }

    LoginDialog dialog;
//    MainDialog dialog;
    dialog.show();





    return a.exec();
}
