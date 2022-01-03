#include <QtGui/QApplication>
#include "tanklevel.hpp"

int main(int argc, char *argv[]){

  // Qt GUI initialisation.
  QApplication app(argc, argv);

  TankLevel mainTankLevel;
  mainTankLevel.show();
    
  // start GUI event loop
  return app.exec();

}
