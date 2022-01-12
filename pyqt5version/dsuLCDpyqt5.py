#!/usr/bin/env python3.6

# TO RUN:  enter the  serial port  you are using  on the  command line,
# argv[1], eg "/dev/ttyUSB".  argv[0] is the program name.


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

# globals

serialPortOpen = "False"

class dsuLCDpyqt5():


    
    def timerCbk(self, textDistance):

        global serialPort
        global serialPortOpen
        

        # serialPort = serial.Serial('/dev/ttyACM0', 9600, timout=0)#open serial port
        # print(serialPortRead.name) # check which port was really used
        # serialPort.close()
        # readStr = serialPort.readlin() # read a '\n' terminated line
        # print_exc(readStr)
        print("dbg:dsuLCD:timerCbk: in timerCbk")


        # # open serial port
        # #   lengthReadStr = len(readStr)
        # readStr = []
        # #readStr = lineEditSerialPort.text() # get serialport entered by user
        # readStr = "/dev/ttyUSB0"
        # #print("lineEditText is = " + readStr)
        # #   print(lengthReadStr)
        # #  readStr[0:lengthReadStr-2]
        # #    print(readStr[0:lengthReadStr-2])
        # if readStr == "":
        #     #print("you need to enter serial port name first")
        #     return

        # print("readStr is portname:" + readStr)
        # lengthDistanceStr = len(readStr)
        # readStr = readStr[0:lengthDistanceStr-11]
        # readStr = ("\'" + readStr + "\'")
        # print("readStr is" + readStr)
        #serialPort = serial.Serial('/dev/ttyUSB0', 9600, timeout=0)

        portNameStr = sys.argv[1] #sys.argv[0] is name of python script
        if (serialPortOpen == "False"):
            print("opening serial port")
            serialPort = serial.Serial(portNameStr, 9600, timeout=0)
            serialPortOpen = "True"
            print("serialPortOpen is " + serialPortOpen)
        #readStr =  ["" for x in  range(15)] # allocate a  string array of
        # siz 15 chars, but shouldn't really  do this in python, use lists
        # instead

        # allocate empty array/ie list.  In python list is a wrapper for a
        # real array  which contains references to  items, not necessarily
        # of the same type


        # Remove \b at  beginning of string and remove \r\nLF  ie CR CR LF
        # LF at  end of string  end of string. This  is a function  of the
        # arduino         sketch         output,        see         sketch
        # distanceSensorUltrasonicLCD.ino.
        readDistanceStr = str( (serialPort.readline()) )
        lengthDistanceStr = len(readDistanceStr)
        distance = readDistanceStr[2:lengthDistanceStr-5]

        print("dbg:dsuLCD:timerCbk: lengthReadStr is " + str(lengthDistanceStr))
        print("dbg:dsuLCD:timerCbk: readDistanceStr is " + readDistanceStr)
        print("dbg:dsuLCD:timerCbk: distance is " + distance)

        textDistance.setText(distance)


    def testfn(self):
        print("calling test fn from dsuLCDpyqt5 class")
            
            




