// Class definition, or implemntation, is placed in .cpp file.

// C++ system header files
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include <QString>    // Qstring

// Serial Port header Files
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


// Qwt system header files, gui related ones in ui_tanklevel.h
//#include <qwt_slider.h>
//#include <qwt_plot.h>


// non-system, local, headers
#include "tanklevel.hpp"
#include "ui_tanklevel.h"



TankLevel::TankLevel(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TankLevel){
  

  //cout<<"dbg: In class DEFAULT CONstructor in .cpp"<<endl;
  //  fprintf(stderr, "dbg: In class DEFAULT CONstructor in .cpp\n");

  // test data:
  double time[] = {10, 20, 30, 40, 50, 60};
  double height[] = {90, 80, 70, 75, 85, 95};


  ui->setupUi(this);

  // One off plot parameters.
  ui->qwtPlot->setTitle("Water Tank Level");

  ui->qwtPlot->setAxisTitle(QwtPlot::xBottom, "Time (minutes)");
  ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, 60);
  ui->qwtPlot->setAxisTitle(QwtPlot::yLeft, "Height (kilo litres)");
  ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, 130.0);


  //  QwtPlotCurve does not allow you to plot only a single x,y value,
  //  it must be a series or at least two sets of values...after all
  //  it's a curve plot.
  //
  //
  // QwtPlotCurve *plotCurve = new QwtPlotCurve("Tank Level over 60min");
  // plotCurve->attach(ui->qwtPlot); // attach the QwtPlot instance,
  //				     // qwtPlot, to plotCurve
  // plotCurve->setPen(QColor(Qt::darkBlue));
  // plotCurve->setStyle(QwtPlotCurve::Lines);
  // plotCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
  //
  // plotCurve->setSamples( time, height, (sizeof(time)/sizeof(double)) );
  // OR
  // plotCurve->setData(time, height, 6);
  // THUS, noWrks:
  // plotCurve->setSamples(&time[0], &height[0], 1);
  // plotCurve->setData(&time[0], &height[0], 1);



  QwtPlotMarker *mark = new QwtPlotMarker();

  QwtSymbol *symM = new QwtSymbol(QwtSymbol::Triangle);
  symM->setPen(QPen(Qt::yellow,2));
  symM->setSize(15);
  mark->setSymbol(symM);
  //
  // further marker specifications:
  //
  // mark->setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
  // mark->setLabelOrientation(Qt::Vertical);
  // mark->setLineStyle(QwtPlotMarker::VLine);
  // mark->setLinePen(QPen(Qt::red, 2, Qt::SolidLine));

  mark->setValue(20, 80);
  // mark->setValue(30, 90);
  // 
  // noWrks as expected, ie loose setValue(20,80) from graph when this
  // new mark is plotted...hence it's called a marker.
  //

  mark->attach(ui->qwtPlot);



  // Plotting a curve, ie two or more sets of (x,y) values.
  //
  // 
  QwtPlotCurve *plotCurve = new QwtPlotCurve("Tank Level over 60min");
  
  // attach the QwtPlot instance, qwtPlot, to plotCurve.
  plotCurve->attach(ui->qwtPlot);

  // Specify (x,y) value marker/symbol.
  QwtSymbol *symPC = new QwtSymbol(QwtSymbol::Star2);
  symPC->setPen(QPen(Qt::darkCyan,2));
  symPC->setSize(7);
  plotCurve->setSymbol(symPC);
  
  // Specify type of curve.
  plotCurve->setPen(QColor(Qt::darkBlue)); // color = darkGreen
  plotCurve->setStyle(QwtPlotCurve::Lines); // style = lineGraph
  plotCurve->setCurveAttribute(QwtPlotCurve::Fitted); // fit curve to symbols
  plotCurve->setRenderHint(QwtPlotItem::RenderAntialiased);

  plotCurve->setSamples( time, height, (sizeof(time)/sizeof(double)) );


  QwtPlotGrid *plotGrid = new QwtPlotGrid();
  plotGrid->attach(ui->qwtPlot);
  plotGrid->enableXMin(true); // enable minor vertical grid lines
  plotGrid->enableYMin(true); // enable minor horozontal grid lines
  plotGrid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));// maj lines black dotted
  plotGrid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));// min lines grey dotted



  // Setup a slot/callback fn that is executed when the timer expires
  // and emits the timout() signal.
  connect( &timer, SIGNAL(timeout()), this, SLOT(timerCbk()) );
  timer.start(1000); // this is a 1sec timer


    
  // cout<<"dbg: Exiting class DEFAULT CONstructor in .cpp"<<endl;
  fprintf(stderr, "dbg: Exiting class DEFAULT CONstructor in .cpp\n");
    
}


TankLevel::~TankLevel(){

  //cout<<"dbg: In class DEFAULT DEstructor in .cpp"<<endl;
//  fprintf(stderr, "dbg: In class DEFAULT DEstructor in .cpp\n");

  // delete all heap stuff, ie a 'new' allocated space stuff

  delete ui;
}


void TankLevel::timerCbk(){

// Qt Timer slot/callback function. QTimer=timer & SLOT=timerCbk().


  //  fprintf(stderr,
  //  "dbg: setupTimerSlot: in timer->TimoutSignal callback function.\n"); 

  int retval;
  char *readStr = new char[10];

  // Arduino serial port device is /dev/ttyACM0, read here.
  // Allocate 12 char array on heap for serial port name.
  char *device = new char[12];
  strcpy(device, "/dev/ttyACM0");


  if ( (retval = readSerialPort(device, readStr)) > 0 ){
    fprintf(stderr,
	    "TankLevel::TankLevel: error in COMMS to  serial port %s.\n",
	    device);
    return;
  }
  
  updatePlotLevel();
  updateAbsoluteLevel(readStr);
  updatePercentageLevel(readStr);
  
}

void TankLevel::updatePlotLevel(){

  //cout<<"dbg: in updatePlotLevel() via C++"<<endl;
  //  fprintf(stderr, "dbg: in updatePlotLevel() via C\n");

//  double time[] = {10, 20, 30, 40, 50, 60};
//  double height[] = {90, 80, 70, 75, 85, 95};
  

//  fprintf(stderr,"dbg: updatePlotL: sizeof time and height arrays is: %ld\n",
//	  sizeof(time)/sizeof(double));


  //  QwtPlotGrid *plotGrid = new QwtPlotGrid();
  //  plotGrid->attach(ui->qwtPlot);

  // Alternative line style in first line graph on examples/curvedemo1.cpp
  //
  // value symbol = Cross in color black
  // plotCurve->setSymbol(new QwtSymbol(QwtSymbol::Cross, Qt::NoBrush,
  // 				     QPen(Qt::black), QSize(5, 5) ) );
  // plotCurve.setPen(QColor(Qt::darkGreen)); // color = darkGreen
  // plotCurve.setStyle(QwtPlotCurve::Lines); // style = lineGraph
  // plotCurve.setCurveAttribute(QwtPlotCurve::Fitted);  // fit curve to crosses

  //plotCurve->setSamples( time, height, (sizeof(time)/sizeof(double)) );


  return;
}


void TankLevel::updateAbsoluteLevel(char *readStr){

  //cout<<"dbg: in updateAbsoluteLevel() via C++"<<endl;
//  fprintf(stderr, "dbg: in updateAbsoluteLevel() via C\n");

  // level of the tank in kiloLitres or cubic m's???
  // int absTankLevel;

//  fprintf(stderr, "dbg: updateAbsL: readInt=%d\n", readInt);
//  fprintf(stderr, "dbg: updateAbsL: readStr=%s\n", readStr);

  ui->sliderAbsoluteLevel->setRange(0.0, 130.0, 1, 1);
  ui->sliderAbsoluteLevel->setScale(1, 130, 5);
  ui->sliderAbsoluteLevel->setScaleMaxMinor(5);

  // absTankLevel = ( pi * (TANK_RADIUS^2) * (TANK_HEIGHT - readInt) );
  ui->sliderAbsoluteLevel->setValue(readInt);
  ui->labelAbsLevel->setText(readStr);

  return;
}


void TankLevel::updatePercentageLevel(char *readStr){


  //cout<<"dbg: in updatePercentageLevel() via C++"<<endl;
//  fprintf(stderr, "dbg: in updatePercentageLevel() via C\n");

  // int percentTankLevel;
  // char *percentTankLevelStr = new char[10];

//  fprintf(stderr, "dbg: updatePercentL: readInt=%d\n", readInt);
//  fprintf(stderr, "dbg: updatePercentL: readStr=%s\n", readStr);

  ui->sliderPercentageLevel->setRange(0, 100, 1, 1); // min,max,step,page
  ui->sliderPercentageLevel->setScale(1, 100, 5); // min,max,step
  ui->sliderPercentageLevel->setScaleMaxMinor(5); // max num of minor ticks
  ui->sliderPercentageLevel->setValue(readInt);
  
  // percentTankLevel = ( (TANK_HEIGHT - (readInt/10)) / TANK_HEIGHT ) * 100
  // convert percentTankLevel to a string percentTankLevelStr
  ui->labelPercentLevel->setText(readStr);
  //  levelValueStr = QString::number(levelValue);

  return;
}


int TankLevel::readSerialPort(char *device, char *readStr){

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

  // Current character read from serial port.
  char readChar = 0;
//  fprintf(stderr, "dbg: readSP: readChar is initialised to: %d\n", readChar);
  
  // readChar's converted to an integer type for use in:
  //   ui->WIDGETname->setValue(readInt);
  readInt = 0;
//  fprintf(stderr, "dbg: readSP: readInt is initialised to: %d\n", readInt);
  
  // Number of digits read, not all the number of chars/bytes read.
  int numDigitsRead = 0;

  // Serial Port buffer/FIFO is sometimes corrupt at program startup.
  // Corruption can also occur later too but this is too hard to cater
  // for.  So skip a number of initial serial port values to cater for
  // most cases.
  int numInitialSPvalues2skip = 1;

  // Must retain value for each timoutCbk() call.
  static int numTotalSPvaluesRead = 0;


  tcgetattr(STDOUT_FILENO, &old_stdio);
 

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


  // Open the terminal/serial port stream: as read, write and non-blocking.
  if ( (tty_fd = open(device, O_RDWR | O_NONBLOCK)) == -1){
    perror("readSerialPort");
    fprintf(stderr, "readSerialPort: error in OPENING serial port %s.\n",
            device);
    return 1;
  }

  cfsetospeed(&tio, B9600); // as per arduino sketch
  cfsetispeed(&tio, B9600); // as per arduino sketch
  tcsetattr(tty_fd, TCSANOW, &tio);
  // test this later: tcsetattr(tty_fd, TCSAFLUSH, &tio);

  //tcflush(tty_fd, TCIFLUSH);   // Flushes data received but not read.

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
    //FD_SET(STDIN_FILENO, &readfds); // watch for chars on stdin=fd=0
    
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
	fprintf(stderr,	"readSerialPort: error READING from serial port %s.\n",
		device);
	return 2;
      }
      else{
//	fprintf(stderr, "dbg: readSP: read() success, readChar=%c\n", readChar);
      }
 
     if ( (retval = write(STDOUT_FILENO, &readChar, 1)) == -1 ){
	perror("readSerialPort");
	fprintf(stderr,	"readSerialPort: error WRITING to  serial port %s.\n",
		device);
	return 3;
      }
      else{
	if ( (readChar != 10) && (readChar != 13) ){
	  // Character read is not a CR(CarriageReturn) or LF(LineFeed)
	  readIntS[numDigitsRead] = readChar - '0';
	  readStr[numDigitsRead] = readChar;
	  
//	  fprintf(stderr, "dbg: readSP: write() success, readIntS[%d]=%d\n",
//		  numDigitsRead, readIntS[numDigitsRead]);
	  
	  numDigitsRead++;
	}
      }


    } //  if (FD_ISSET(tty_fd, &readfds)){

    
    // REMEMBER sometimes new output at serial port before finished here
    // that is may need greater delay at arduino sketch before next
    // measurment is displayed.

     
  }// end: while (readChar != 10){
  


  // Calculate the integer value of all digits read.
    if (numDigitsRead == 1){
    readInt = readIntS[0];
  }
  else if (numDigitsRead == 2){
    readInt = (readIntS[0]*10) + readIntS[1];
  }
  else if (numDigitsRead == 3){
    readInt = (readIntS[0]*100) + (readIntS[1]*10) + readIntS[2];
  }
  fprintf(stderr, "dbg: readSP: numDigitsRead=%d\n", numDigitsRead);
  fprintf(stderr, "dbg: readSP: readInt=%d\n", readInt);

  numTotalSPvaluesRead++;
	  

  // Skip 'numInitialSPvalues2skip' values/integers.
  if (numTotalSPvaluesRead > numInitialSPvalues2skip){
    // string terminator = NULL = 0base10
    readStr[numDigitsRead] = '\0';
  }
  else{
    readStr[0] = '\0';
    readInt = 0;
  }
  fprintf(stderr, "dbg: readSP: readStr=%s\n", readStr);


  //tcflush(tty_fd, TCIOFLUSH);   // Flushes data received but not read.
  
  // close(tty_fd) on its own does not work as compiler trys to use
  // QWidget::close.  Use :: prefix to use global close fn.
  //
  // No need for error handling in close as that would be a coding err??
  ::close(tty_fd);
  tcsetattr(STDOUT_FILENO, TCSANOW, &old_stdio);

  return 0; // success
}

