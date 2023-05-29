/*
   Created by DIYables

   This example code is in the public domain

   Product page: https://diyables.io/products/4-digit-7-segment-display-led-74hc595-driver-with-4-dots
*/

#include <DIYables_4Digit7Segment_74HC595.h> // DIYables_4Digit7Segment_74HC595 library

#define SCLK  7  // The Arduino pin connected to SCLK
#define RCLK  6  // The Arduino pin connected to RCLK
#define DIO   5  // The Arduino pin connected to DIO

DIYables_4Digit7Segment_74HC595 display(SCLK, RCLK, DIO);

void setup() {
  Serial.begin(9600);

  // display 9.3°C by controlling digit by digit
  display.clear();
  display.setNumber(1, 9);              // set 9 at the 1st digit
  display.setDot(1);                    // set . at the 1st digit
  display.setNumber(2, 3);              // set 3 at the 2nd digit
  display.setChar(3, SegChars::DEGREE); // set ° at the 3rd digit
  display.setChar(4, SegChars::C);      // set C at the 3rd digit
  display.show();                       // show on the display
}

void loop() {
  display.loop(); // MUST call the display.loop() function in loop()

  // DO SOMETHING HERE
  // NOTE: do NOT use the delay() function in loop because it affects to the multiplexing
}