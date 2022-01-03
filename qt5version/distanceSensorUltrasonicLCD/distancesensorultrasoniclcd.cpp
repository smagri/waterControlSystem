// Serial Port header Files

#include <iostream>
#include <string>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstdlib>




#include "distancesensorultrasoniclcd.h"
#include "ui_distancesensorultrasoniclcd.h"


distanceSensorUltrasonicLCD::distanceSensorUltrasonicLCD(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::distanceSensorUltrasonicLCD)
{
  ui->setupUi(this);

  //ui->sliderDistance->setRange(0, 100, 1, 1); // min,max,step,page
  //ui->sliderDistance->setScale(1, 100, 5); // min,max,step
  //ui->sliderDistance->setScaleMaxMinor(5); // max num of minor ticks
  //ui->sliderDistance->setValue(readInt);
  ui->QwtTextLabelDistance->setText("XXXX");

  ui->QwtPlotDistance->setTitle("Ultrasonic Sensor Distance");

  ui->QwtPlotDistance->setAxisTitle(QwtPlot::xBottom, "Time (hours)");
  ui->QwtPlotDistance->setAxisScale(QwtPlot::xBottom, 0, 24);
  ui->QwtPlotDistance->setAxisTitle(QwtPlot::yLeft, "Distance (cm)");
  ui->QwtPlotDistance->setAxisScale(QwtPlot::yLeft, 0.0, 400.0);


  // Setup a slot/callback fn that is executed when the timer expires
  // and emits the timout() signal.
  connect( &timer, SIGNAL(timeout()), this, SLOT(timerCbk()) );
  timer.start(1000); // this is a 1sec timer


}

void distanceSensorUltrasonicLCD::timerCbk(void){
// Qt Timer slot/callback function. QTimer=timer & SLOT=timerCbk().

  std::cout << "dbg: readSP: timerCbk: entered" << "\n";

  int retval;
  char readStr[40]; // String read from serial port

  // Arduino serial port device is /dev/ttyACM0, read here.
  // Allocate 12 char array on heap for serial port name.
  char device[20] = "/dev/ttyUSB0";
  //strcpy(device, "/dev/ttyUSB0");


  if ( (retval = readSerialPort(device, readStr)) > 0 ){
    fprintf(stderr,
	    "distnaceSensorUltrasonicLCD::timerCbk: error in COMMS to serial port %s.n",
            device);
    return;
  }
  else{
    ui->QwtTextLabelDistance->setText(readStr);
    double readStr2double = std::atof(readStr);
    ui->QwtSliderDistance->setValue(readStr2double);
  }

  
}



int distanceSensorUltrasonicLCD::readSerialPort(char *device, char *readStr){

  std::cout << "dbg: readySP: entered" << "\n";

  //  int ctty = 0, cstdin = 0;
  struct termios tio;
  struct termios stdio;
  struct termios old_stdio;
  int tty_fd;

  fd_set readfds; // The set of file descriptors probed for 'ready for
                  // reading', that is read() system call will not
                  // block/sleep.

  // select() timout value in seconds and microseconds.
  // struct timeval timeout;

  int retval;
  unsigned char readChar = 'x';  // Current character read from serial port.
  int numCharsRead = 0; // Number of chars read from serial.


  tcgetattr(STDOUT_FILENO, &old_stdio);
 
  // Input serial port to communicate with as command line argument
  //???printf("Please start with %s /dev/ttyS1 (for example)\n", argv[0]);

  // Configure stdin and stout, as part make them non-blocking streams.
  memset(&stdio ,0, sizeof(stdio));
  stdio.c_iflag=0;
  stdio.c_oflag=0;
  stdio.c_cflag=0;
  stdio.c_lflag=0;
  stdio.c_cc[VMIN]=1;
  stdio.c_cc[VTIME]=0;
  tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
  tcsetattr(STDOUT_FILENO, TCSAFLUSH, &stdio);
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // make the reads non-blocking
 
  // Configure the terminal/serial port.
  memset(&tio, 0, sizeof(tio));
  tio.c_iflag=0;
  tio.c_oflag=0;
  tio.c_cflag=CS8|CREAD|CLOCAL; // 8n1, see termios.h for more information
  tio.c_lflag=0;
  tio.c_cc[VMIN]=1;
  tio.c_cc[VTIME]=5;

  // system calls ie open/read/write() need error handling

  // Open the terminal/serial port stream: as read, write and non-blocking.
  if ( (tty_fd = open(device, O_RDWR | O_NONBLOCK)) == -1){
    perror("readSerialPort");
    fprintf(stderr, "readSerialPort: error in OPENING serial port device.\n");
    //return 1;
  }
  else{
    fprintf(stderr, "readSerialPort: successfully opened device = %s\n", device);

  }

  
  cfsetospeed(&tio, B9600); // as per arduino sketch
  cfsetispeed(&tio, B9600); // as per arduino sketch
  tcsetattr(tty_fd, TCSANOW, &tio);


  // Loop until Line Feed(ie LF char = 10base10) character is found,
  // thus all chars for the next water level value have been received.
  while (readChar != 10){
    // Clear and reset fds ready for next select() call.
    //
    // This is as per examples in select_tut(2)) and Stevens and also,
    // ~proj/atnf/cabb/src/callbacks.c.
    //
    FD_ZERO(&readfds); // clear/reset read file descriptors
    FD_SET(tty_fd, &readfds); // watch for chars on tty_fd/serial port.
    //??????FD_SET(STDIN_FILENO, &readfds); // watch for chars on stdin=fd=0
    
    // Timeout from the select() call after timeout.sec/usec of non-activity.
    //
    // select() should really return way before so this is just a safety catch.
    // Set timeout = NULL for indefinate blocking/sleeping, and = 0 for polling.
    //
    //timeout.tv_sec = 60; // 1 minute timeout for select().
    //timeout.tv_usec = 0;

    // select() allows you to monitor more than one file descriptor at
    // a time.  It blocks(ie sleeps) till one or more file descriptors
    // become 'ready' for some io operation.  A file descriptor is
    // 'ready' when a corresponding type of system call(eg read()) for
    // readfds)will not block/sleep.
    if ( (retval = select((FD_SETSIZE+1), &readfds,
                          (fd_set *) NULL,(fd_set *) NULL, NULL))  == -1 ){
      perror("readSerialPort");
      fprintf(stderr, "readSerialPort: select returned %d\n", retval);
      return 1;
    }

 // More than one fd can be ready at a time.  That is, character
    // present on the serial port and at stdin simultaneously.
    if (FD_ISSET(tty_fd, &readfds)){
      // Data is available on the serial port, read it from port and
      // print it out to stdout.
      if ( (retval = read(tty_fd, &readChar, 1)) == -1){
        perror("readSerialPort");
        fprintf(stderr, "readSerialPort: error READING from serial port %s.\n",
                device);
        return 2;
      }

      
      if ( (retval = write(STDERR_FILENO, &readChar, 1)) == -1 ){
         perror("readSerialPort");
         fprintf(stderr, "readSerialPort: error WRITING to  serial port %s.\n",
                 device);
         return 3;
       }
       else{
         if ( (readChar != 10) && (readChar != 13) ){
          // Character read is not a CR(CarriageReturn) or LF(LineFeed)
          //readIntS[numDigitsRead] = readChar - '0';
          readStr[numCharsRead++] = readChar;
          
//        fprintf(stderr, "dbg: readSP: write() success, readIntS[%d]=%d\n",
//                numDigitsRead, readIntS[numDigitsRead]);
	 }
	 else{
	   // Last character of string has just been read.
	   readStr[numCharsRead] = '\0';
	 }
       }


    } //  if (FD_ISSET(tty_fd, &readfds)){

    // REMEMBER sometimes new output at serial port before finished here
    // that is may need greater delay at arduino sketch before next
    // measurment is displayed.

  } // end: while (readChar != 10){


  // close(tty_fd) on its own does not work as compiler trys to use
  // QWidget::close.  Use :: prefix to use global close fn.
  //
  // No need for error handling in close as that would be a coding err??
  ::close(tty_fd);
  tcsetattr(STDOUT_FILENO, TCSANOW, &old_stdio);

  return 0; // success
}

distanceSensorUltrasonicLCD::~distanceSensorUltrasonicLCD(){

  // delete all heap stuff, ie a 'new' allocated space stuff
  delete ui;
}
