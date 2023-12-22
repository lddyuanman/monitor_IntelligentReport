#include "MonitorSys.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MonitorSys w;
    w.show();
    return a.exec();
}
