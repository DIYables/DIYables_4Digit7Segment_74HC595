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

  display.printInt(-13, false); // you can display a value from -999 to 9999
  //display.printInt(-132, false);
  //display.printInt(9132, false);
  //display.printInt(132, false);
  //display.printInt(32, false);
  //display.printInt(2, false);
  //display.printInt(2, true);
}

void loop() {
  display.loop(); // MUST call the display.loop() function in loop()

  // DO SOMETHING HERE
  // NOTE: do NOT use the delay() function in loop because it affects to the multiplexing
}