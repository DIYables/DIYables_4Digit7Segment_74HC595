/*
 * DIYables_4Digit7Segment_74HC595 - Blink Example
 *
 * Blink integer, float, and text on a 4-digit 7-segment display driven
 * by 74HC595. Uses off() to stop the display and on() to restart it.
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

// States: 0 = blink int, 1 = blink float, 2 = blink text
int phase = 0;
int blinkCount = 0;
bool isOn = true;
unsigned long lastAction = 0;
unsigned long pauseUntil = 0;

void setup() {
  Serial.begin(9600);
  display.begin();
  Serial.println("4-Digit 7-Segment 74HC595 - Blink Example");
  display.print(1234);
  Serial.println("Blinking: 1234");
}

void loop() {
  display.loop();  // Must be called frequently to refresh the display

  unsigned long now = millis();

  // Pause between phases
  if (now < pauseUntil) return;

  if (now - lastAction >= 300) {
    lastAction = now;

    if (isOn) {
      display.off();
      isOn = false;
    } else {
      display.on();
      isOn = true;
      blinkCount++;

      if (blinkCount >= 5) {
        blinkCount = 0;
        pauseUntil = now + 1000;

        phase++;
        if (phase > 2) phase = 0;

        switch (phase) {
          case 0:
            display.print(1234);
            Serial.println("Blinking: 1234");
            break;
          case 1:
            display.print(12.34);
            Serial.println("Blinking: 12.34");
            break;
          case 2:
            display.print("HELP");
            Serial.println("Blinking: HELP");
            break;
        }
      }
    }
  }
}
