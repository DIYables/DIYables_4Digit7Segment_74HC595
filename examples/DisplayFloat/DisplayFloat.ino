/*
   Created by DIYables

   This example code is in the public domain

   Product page: https://diyables.io/products/4-digit-7-segment-display-led-74hc595-driver-with-4-dots

   TESTED HARDWARE
    - Arduino Uno R3
    - Arduino Uno R4 WiFi
    - Arduino Uno R4 Minima
    - Arduino Mega
    - Arduino Due
    - Arduino Giga
    - DIYables STEM V3: https://diyables.io/stem-v3
    - DIYables STEM V4 IoT: https://diyables.io/stem-v4-iot
    - DIYables STEM V4B IoT: https://diyables.io/stem-v4b-iot
    - DIYables STEM V4 Edu: https://diyables.io/stem-v4-edu
    - DIYables MEGA2560 R3: https://diyables.io/atmega2560-board
    - DIYables ESP32 Board: https://diyables.io/esp32-board
    - DIYables ESP32 S3, Uno-form factor: https://diyables.io/esp32-s3-uno
    - It is expected to work with other boards
*/

#include <DIYables_4Digit7Segment_74HC595.h> // DIYables_4Digit7Segment_74HC595 library

#define SCLK  7  // The Arduino pin connected to SCLK
#define RCLK  6  // The Arduino pin connected to RCLK
#define DIO   5  // The Arduino pin connected to DIO

DIYables_4Digit7Segment_74HC595 display(SCLK, RCLK, DIO);

void setup() {
  Serial.begin(9600);
  display.printFloat(-9.2,  1, false);
  //display.printFloat(-92.4, 1, false);
  //display.printFloat(-9.24, 2, false);
  //display.printFloat(192.4, 1, false);
  //display.printFloat(19.24, 2, false);
  //display.printFloat(1.924, 3, false);
}

void loop() {
  display.loop(); // MUST call the display.loop() function in loop()

  // DO SOMETHING HERE
  // NOTE: do NOT use the delay() function in loop because it affects to the multiplexing
}