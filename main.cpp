#include "calibdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString cfgfile("~/.usbcam.ini");
    if(argc >= 2)
        cfgfile = argv[1];
    CalibDialog w(cfgfile);
    w.show();

    return a.exec();
}
