# waterSysCtrl

04jan2022

This project is  the software developed for the  illabunda eco village
water control system.  Currently, prototype breadboard designs and PCB
module used is placed in repository:

https://github.com/smagri/kicad_distanceSensorUltrasonicLCD.git

It  is  a  distance  sensor  using a  HC-SR04  ultrasonic  sensor  and
displaying the  the distance on  a 1602LCD. See images/  directroy, no
enclosure has yet been made.

However, the design  can be used a general ultrasonic  sensor based as
an approximate distance measure from 2cm  - 400cm. There are new plans
for a PyDroid3 python based TCP  network RF version to be created now.

Included in the waterSystemControl repository:

* is the arduino pro  mini sketch code, /arduino/LCD1602.HC-SR04.sketch
  folder.

* /hardw folder has the relevent hardware datasheets

* /qt5version folder of the GUI control app

* /pyqt5version folder  is the  pyqt5version of  the GUI  control app,
  with the aim  to integrate into PyDroid python based  TCP network RF
  version  in the  long run.   Inital  testing of  the basic  starting
  script has occured and it works on PyDroid3.

