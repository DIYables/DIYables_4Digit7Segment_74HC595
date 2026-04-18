/*
 * DIYables_4Digit7Segment_74HC595 - Time Example
 *
 * Display time in HH.MM format with a blinking dot separator on a 4-digit
 * 7-segment display driven by 74HC595.
 * Note: This module has dots only (no colon). The dot on digit 1 acts as
 * the time separator.
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

int hours = 12;
int minutes = 30;
bool colonOn = true;
unsigned long lastToggle = 0;

void setup() {
  Serial.begin(9600);
  display.begin();
  Serial.println("4-Digit 7-Segment 74HC595 - Time Example");
  Serial.println("Displaying 12:30 with blinking dot separator");
}

void loop() {
  display.loop();  // Must be called frequently to refresh the display

  if (millis() - lastToggle >= 500) {
    lastToggle = millis();
    display.printTime(hours, minutes, colonOn);
    colonOn = !colonOn;  // Toggle dot separator every 500ms for blinking effect
  }
}
