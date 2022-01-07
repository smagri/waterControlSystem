#!/usr/bin/env python3.6

import sys
import serial
import io
import time

#imports all the modules you need to create a GUI into the current namespace
#from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QWidget, QTextEdit
#from PyQt5.QtGui import QPalette

from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QPalette


def timerCbk():

    

    # serialPort = serial.Serial('/dev/ttyACM0', 9600, timout=0)#open serial port
    # print(serialPortRead.name) # check which port was really used
    # serialPort.close()
    # readStr = serialPort.readlin() # read a '\n' terminated line
    # print_exc(readStr)
    print("dbg:dsuLCD:timerCbk: in timerCbk")

    lineEditSerialPort.setText(serialPort.name)

    
    #readStr =  ["" for x in  range(15)] # allocate a  string array of
    # siz 15 chars, but shouldn't really  do this in python, use lists
    # instead

    # allocate empty array/ie list.  In python list is a wrapper for a
    # real array  which contains references to  items, not necessarily
    # of the same type
    readStr = [] 
    readStr = str( (serialPort.readline()) )
    lengthReadStr = len(readStr)

    # Remove \b at  beginning of string and remove \r\nLF  ie CR CR LF
    # LF at  end of string  end of string. This  is a function  of the
    # arduino         sketch         output,        see         sketch
    # distanceSensorUltrasonicLCD.ino.
    distance = readStr[2:lengthReadStr-5]

    print("dbg:dsuLCD:timerCbk: lengthReadStr is " + str(lengthReadStr))
    print("dbg:dsuLCD:timerCbk: readStr is " + readStr)
    print("dbg:dsuLCD:timerCbk: distance is " + distance)

    textDistance.setText(distance)


    
if __name__ == "__main__":

    # Creating an object of the  QApplication class. Every UI app must
    # create an  instance of  QApplication, as a  sort of  entry point
    # into the app. If you do not create it, errors will be shown.

    # sys.argv is  the list  of command-line  parameters that  you can
    # pass to the  application when launching it through  the shell or
    # while automating  the interface.  Use app  = QApplication([]) if
    # no arguments will be passed.
    app = QApplication(sys.argv)
    #  set a syle, can be fusion, windows, mac..app.setStyle("Fusion")


    # Create an object of the QWidget class. QWidget is the base class of
    # all UI objects in Qt.
    w = QWidget()

    # set dimensions of widget (pixel,pixel) or (px,px)
    w.resize(400,400)

    # Widgets can be nested and this is the outermost/top widget, that
    # is the widget with no parent.
    #title = "Ultrasonic Distance Sensor with LCD display" + "\\n"
    #w.setWindowTitle(title)
    #w.setWindowTitle("(HC-SRO4 with 1602 LCD)")
    w.setGeometry(10,10,640,480)

    labelTitle = QLabel("Ultrasonic Distance Sensor with LCD display", w)
    labelPCBdetails = QLabel("(using HCSR04 with 1602LCD)", w)
    labelGap = QLabel("")
    labelGap1 = QLabel("")
    labelGap2 = QLabel("")

    labelSerialPort = QLabel("Enter Serial Port name, eg: /dev/ttyACM0")
    lineEditSerialPort = QLineEdit(w)
    
    labelGap3 = QLabel("")
    labelDistance = QLabel("Distance (cm)", w)
    #labelDistance.setWordWrap(True)
    labelDistance.move(200,200)
    textDistance = QTextEdit("",w)

    
    # Put within a standard verticallayoutwidget
    vbox = QVBoxLayout(w)
    vbox.addWidget(labelTitle)
    vbox.addWidget(labelPCBdetails)
    vbox.addWidget(labelGap)
    vbox.addWidget(labelGap1)

    vbox.addWidget(labelSerialPort)
    vbox.addWidget(lineEditSerialPort)

    vbox.addWidget(labelGap2)
    vbox.addWidget(labelGap3)
    vbox.addWidget(labelDistance)
    vbox.addWidget(textDistance)


    # FIXME: this does not seem to work for a dark background
    # change colours of application gui
    #qp = QPalette() # create object of class QPalette, QtGui module
                    # required

     # use QPalette method of QPalette class
    #qp.setColor(QPalette.QTextEdit, Qt.blue)
    #qp.setColor(QPalette.Window, Qt.black)

    
    # In  GUI based  applications,  functions are  executed  based on  the
    # actions  performed by  the user,  like hovering  over an  element or
    # clicking a button. These actions  are called events. Recall that the
    # app.exec_() method transfers  control to the Qt  event-loop. This is
    # what the event  loop is there for: to listen  for events and perform
    # actions in response.
    
    # Whenever an  event occurs,  like a user  clicking a  button, the
    # corresponding Qt  widget raises a  signal. These signals  can be
    # connected to  python functions,  any function can  be a  slot in
    # python,  so that  the  function  is executed  when  a signal  is
    # triggered. These functions are called slots in Qt lingo.
    
    # Basic  syntax to  trigger a  slot  function in  response to  the
    # signal      from      an      event      is      as      follows
    #                   widget.signal.connect(slot)

    # textDistance.signal.connect(slotReadSerialPort)
    # textEditDistance.setPlainText("Hello PyQt5!\nfrom pythonpyqt.com")
    timer = QTimer() # create a timer object
    timer.timeout.connect(timerCbk)
    timer.start(200) # milliseconds
    #textDistance.textChanged.connect(timerCbk)
    #textDistance.setText.connect(timerCbk)

    # open serial port
    serialPort = serial.Serial('/dev/ttyUSB0', 9600, timeout=0)
    # check which port was really used
    print("serial port opened is " + serialPort.name)

       
    # Display the widget onthe monitor screen.
    w.show()

    # Start the Qt/C++ event loop.

    # note: exec_ is used in instead of exec as this is a python keywoard
    sys.exit(app.exec_())


    serialPort.close()
    
