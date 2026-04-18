/*
 * DIYables_4Digit7Segment_74HC595 - Float Example
 *
 * Display float numbers on a 4-digit 7-segment display driven by 74HC595.
 * Shows auto and manual decimal places, with optional zero-padding.
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
  Serial.println("4-Digit 7-Segment 74HC595 - Float Example");
}

void loop() {
  // Auto decimal placement
  display.print(1.5);       // Shows " 1.5"
  Serial.println("Auto decimal: 1.5");
  display.delay(2000);

  display.print(12.34);     // Shows "12.34"
  Serial.println("Auto decimal: 12.34");
  display.delay(2000);

  display.print(3.141);     // Shows "3.141"
  Serial.println("Auto decimal: 3.141");
  display.delay(2000);

  display.print(-1.2);      // Shows "-1.20"
  Serial.println("Auto decimal: -1.20");
  display.delay(2000);

  display.print(0.5);       // Shows " 0.5"
  Serial.println("Auto decimal: 0.5");
  display.delay(2000);

  // Fixed decimal places
  display.print(23.5, 1);   // 1 decimal place: shows "23.5"
  Serial.println("1 decimal place: 23.5");
  display.delay(2000);

  display.print(1.5, 2);    // 2 decimal places: shows "1.50"
  Serial.println("2 decimal places: 1.50");
  display.delay(2000);

  // Zero-padded
  display.print(1.5, 2, true);  // Shows "01.50"
  Serial.println("2 decimal places, zero-padded: 01.50");
  display.delay(2000);
}
