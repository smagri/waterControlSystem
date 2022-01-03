// serial comms
// all in /usr/include
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include </usr/include/unistd.h>
#include <fcntl.h>
#include <termios.h>

// ultrasonic sensor
#include "Ultrasonic.h"


Ultrasonic ultrasonic(12,13);


void setup(){
  Serial.begin(9600);
  Serial.println("Ultrasonic Water Level Sensor");
  delay(1000);
}


void loop(){

  // This prints output to the serial port gui within the arduinoIDE
  Serial.println(ultrasonic.Ranging(CM));
  Serial.println("cm");
  delay(100);		

  // This prints output to stdout file descriptor = 1
  struct termios tio;
  struct termios stdio;
  struct termios old_stdio;
  int tty_fd;
  
  unsigned char readChar='D';
  tcgetattr(STDOUT_FILENO, &old_stdio);
 
  // printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);

  // set standard-input/output, ie stdin and stdout(/stderr?)
  memset(&stdio, 0, sizeof(stdio));
  stdio.c_iflag=0;
  stdio.c_oflag=0;
  stdio.c_cflag=0;
  stdio.c_lflag=0;
  stdio.c_cc[VMIN]=1;
  stdio.c_cc[VTIME]=0;
  tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
  tcsetattr(STDOUT_FILENO, TCSAFLUSH, &stdio);
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // make the reads non-blocking
 
  // set serial port-input/output, ie ttyS0...
  memset(&tio, 0, sizeof(tio));
  tio.c_iflag=0;
  tio.c_oflag=0;
  tio.c_cflag=CS8|CREAD|CLOCAL; // 8n1, see termios.h for more information
  tio.c_lflag=0;
  tio.c_cc[VMIN]=1;
  tio.c_cc[VTIME]=5;
 
  tty_fd = open("/dev/ttyS1", O_RDWR | O_NONBLOCK);      
  cfsetospeed(&tio, B9600); // 115200 baud is default
  cfsetispeed(&tio, B9600); // 115200 baud is default
 
  tcsetattr(tty_fd, TCSANOW, &tio);

  // replace this loop with
  while (readChar!='q'){

    if (read(tty_fd, &readChar, 1) > 0){
      // if new data is available on the serial port, print it out   
      write(STDOUT_FILENO, &readChar, 1);
    }
    if (read(STDIN_FILENO, &readChar, 1) > 0){
      // if new data is available on the console, send it to the serial port
      write(tty_fd, &readChar, 1);
    }

  }
 
  close(tty_fd);
  tcsetattr(STDOUT_FILENO, TCSANOW, &old_stdio);
 
  return EXIT_SUCCESS;
	
}
