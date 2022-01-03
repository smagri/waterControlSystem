#include <QtGui/QApplication>
#include "tanklevel.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TankLevel w;
    w.show();
    
    return a.exec();
}
