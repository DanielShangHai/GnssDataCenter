#include "gnssmanagement.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GnssManagement w;
    w.show();

    return a.exec();
}
