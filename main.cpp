#include "login.h"
#include "chatwin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QVector<int>>("QVector<int>");
    /*
     * //qt6中DPI 缩放 qt5不支持
     * QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
    */
    QApplication a(argc, argv);
/*
    login login;
    login.show();
*/

      //测试时使用不需要登录
      chatwin* chatWin = new chatwin;
      chatWin->setWindowFlags(Qt::FramelessWindowHint);
      chatWin->show();



    return a.exec();
}
