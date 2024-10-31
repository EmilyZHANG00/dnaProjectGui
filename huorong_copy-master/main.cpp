#include "mainwnd.h"
#include <QApplication>
#include "appinit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));

    AppInit::Instance()->start();

    MainWnd w;
    w.show();

    return a.exec();
}
