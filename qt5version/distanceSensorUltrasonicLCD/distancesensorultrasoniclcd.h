#ifndef DISTANCESENSORULTRASONICLCD_H
#define DISTANCESENSORULTRASONICLCD_H

#include <QTimer>
#include <QMainWindow>

namespace Ui {
  class distanceSensorUltrasonicLCD;
}

class distanceSensorUltrasonicLCD : public QMainWindow
{
  Q_OBJECT

public:
  explicit distanceSensorUltrasonicLCD(QWidget *parent = 0);
  ~distanceSensorUltrasonicLCD();

  


private slots:
  // QTimer, timer, slot/callback function.
  void timerCbk(void);



private:
  int readSerialPort(char *device, char *readStr);		  


  // Pointer/Referecne to GUI wigets in this class.
  Ui::distanceSensorUltrasonicLCD *ui;

  // Qt periodic event timer, when it's timout() signal occurs the
  // timerCbk() slot/callback function is called.
  QTimer timer;

};

#endif // DISTANCESENSORULTRASONICLCD_H
