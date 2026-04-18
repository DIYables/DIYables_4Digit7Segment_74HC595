/*
 * DIYables_4Digit7Segment_74HC595 - IndividualDigits Example
 *
 * Sets individual digits, characters, and dot on a 4-digit
 * 7-segment display driven by 74HC595.
 *
 * Tutorial: https://diyables.io/products/4-digit-7-segment-display-led-74hc595-driver-with-4-dots
 *
 * TESTED HARDWARE:
 * - Arduino Uno R3
 * - Arduino Uno R4 WiFi
 * - Arduino Uno R4 Minima
 * - Arduino Mega
 * - Arduino Due
 * - Arduino Giga
 * - DIYables STEM V3: https://diyables.io/stem-v3
 * - DIYables STEM V4 IoT: https://diyables.io/stem-v4-iot
 * - DIYables STEM V4B IoT: https://diyables.io/stem-v4b-iot
 * - DIYables STEM V4B Edu: https://diyables.io/stem-v4-edu
 * - DIYables MEGA2560 R3: https://diyables.io/atmega2560-board
 * - DIYables Nano R3: https://diyables.io/nano-board
 * - DIYables ESP32 Board: https://diyables.io/esp32-board
 * - DIYables ESP32 S3, Uno-form factor: https://diyables.io/esp32-s3-uno
 * - It is expected to work with other boards
 */

#include <DIYables_4Digit7Segment_74HC595.h>

// Pin configuration - change these to match your wiring
#define SCLK_PIN 7   // Serial clock (SH_CP)
#define RCLK_PIN 6   // Register clock / latch (ST_CP)
#define DIO_PIN  5   // Data (DS)

DIYables_4Digit7Segment_74HC595 display(SCLK_PIN, RCLK_PIN, DIO_PIN);

void setup() {
  Serial.begin(9600);
  display.begin();
  Serial.println("4-Digit 7-Segment 74HC595 - Individual Digits Example");
}

void loop() {
  // Set individual numbers on each digit position
  display.clear();
  display.setNumber(0, 1);
  display.setNumber(1, 2);
  display.setNumber(2, 3);
  display.setNumber(3, 4);
  Serial.println("Displaying: 1234");
  display.delay(2000);

  // Turn on dot on each digit one by one
  display.setDot(0, true);
  Serial.println("Dot on digit 0: 1.234");
  display.delay(1500);

  display.setDot(1, true);
  Serial.println("Dots on digits 0-1: 1.2.34");
  display.delay(1500);

  display.setDot(2, true);
  Serial.println("Dots on digits 0-2: 1.2.3.4");
  display.delay(1500);

  display.setDot(3, true);
  Serial.println("All 4 dots on: 1.2.3.4.");
  display.delay(1500);

  // Turn off all dots
  display.setDot(0, false);
  display.setDot(1, false);
  display.setDot(2, false);
  display.setDot(3, false);
  Serial.println("All dots off: 1234");
  display.delay(2000);

  // Set individual characters
  display.clear();
  display.setChar(0, 'H');
  display.setChar(1, 'E');
  display.setChar(2, 'L');
  display.setChar(3, 'P');
  Serial.println("Displaying: HELP");
  display.delay(2000);

  // Mix characters and numbers with dot
  display.clear();
  display.setChar(0, 'A');
  display.setNumber(1, 3);
  display.setChar(2, 'b');
  display.setNumber(3, 7);
  display.setDot(1, true);
  Serial.println("Displaying: A3.b7");
  display.delay(2000);

  // Set custom segments (draw a square on digit 0)
  display.clear();
  display.setSegments(0, SEG_A | SEG_B | SEG_F | SEG_G);
  display.setSegments(1, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F);  // 0
  display.setSegments(2, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G);          // E
  display.setSegments(3, SEG_D | SEG_E | SEG_F);                          // L
  Serial.println("Custom segments");
  display.delay(2000);

  // Blinking all 4 dots
  display.clear();
  display.setNumber(0, 1);
  display.setNumber(1, 2);
  display.setNumber(2, 3);
  display.setNumber(3, 0);
  Serial.println("Blinking all 4 dots");
  for (int i = 0; i < 5; i++) {
    display.setDot(0, true);
    display.setDot(1, true);
    display.setDot(2, true);
    display.setDot(3, true);
    display.delay(500);
    display.setDot(0, false);
    display.setDot(1, false);
    display.setDot(2, false);
    display.setDot(3, false);
    display.delay(500);
  }
  display.delay(1000);
}
