#include <iostream>


#include "distancesensorultrasoniclcd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  
  // Qt GUI initialisation.
  QApplication a(argc, argv);
  distanceSensorUltrasonicLCD w;
  std::cerr << "before show" << std::endl;


  w.show();


  std::cerr  << "after show" << std::endl;

  // start GUI event loop
  return a.exec();
}
