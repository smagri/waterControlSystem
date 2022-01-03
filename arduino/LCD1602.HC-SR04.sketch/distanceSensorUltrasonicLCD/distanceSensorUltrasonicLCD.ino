
#include <LiquidCrystal.h>

#include <Ultrasonic.h>

//#include "Ultrasonic.h"
//#include <LiquidCrystal.h>

#define LCD_OUTPUT 1
#define SERIAL_OUTPUT 1

// LCD-10862 LCD with RGB backlighting used
LiquidCrystal lcd(11, 10, 4, 5, 6, 7);

//LiquidCrystal lcd(11, 10, 9, 4, 5, 6);

// orig:LiquidCrystal lcd(11, 10, 4, 5, 6, 7);
//LiquidCrystal lcd(11, 10, 7, 6, 5, 4);
//LiquidCrystal lcd(10, 11, 4, 5, 6, 7);
//LiquidCrystal lcd(11, 10, 5, 4, 3, 2);

// Ultrasonic Level Sensor connected via digital i/o pins 12 & 13 on arduino
Ultrasonic ultrasonic(12, 13);


void setup(){

#ifdef LCD_OUTPUT
  // Setup output to lcd display and display welcome message.
  lcd.begin(16, 2); // setup LCD for 16chars on two lines
  //lcd.begin(16, 1); // setup LCD for 16chars on two lines

  lcd.print("Ultrasonic Water");
  lcd.setCursor(0, 1);
  lcd.print("Level Sensor...");
  delay(2000);
#endif

#ifdef SERIAL_OUTPUT
  // Setup output to serial port.
  Serial.begin(9600);
#endif

}


void loop(){

#ifdef LCD_OUTPUT
  // Output water level to lcd.
  lcd.clear();
  lcd.setCursor(0, 0);
  //lcd.setCursor(0, 1);

  lcd.print("Water @ ");
  lcd.print(ultrasonic.Ranging(CM));
  lcd.print("cm.");
  
  // 0.1 sec seems to be minimum time before next sensor reading ready.  That
  // is next time ultrasonic.Ranging(CM) contains a valid/detected value.
  delay(100);
#endif

#ifdef SERIAL_OUTPUT
  // Output water level to serial port.
  Serial.println(ultrasonic.Ranging(CM));
  //Serial.println('\n');
  // Not complicate things.
  //Serial.println("cm");
  
  delay(100);
#endif

  //delay(100); // delay in ms
}
