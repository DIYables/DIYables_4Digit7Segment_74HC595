/*
 * DIYables_4Digit7Segment_74HC595 - Integer Example
 *
 * Display integer numbers on a 4-digit 7-segment display driven by 74HC595.
 * Shows integers from -999 to 9999, with optional zero-padding.
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

int numbers[] = {0, 42, 1234, -5, -123, 9999};
int numCount = 6;
int currentIndex = 0;
bool showZeroPad = false;
unsigned long lastChange = 0;

void setup() {
  Serial.begin(9600);
  display.begin();
  Serial.println("4-Digit 7-Segment 74HC595 - Integer Example");
}

void loop() {
  display.loop();  // Must be called frequently to refresh the display

  if (millis() - lastChange >= 2000) {
    lastChange = millis();

    if (!showZeroPad) {
      display.print(numbers[currentIndex]);
      Serial.print("Displaying: ");
      Serial.println(numbers[currentIndex]);

      currentIndex++;
      if (currentIndex >= numCount) {
        currentIndex = 0;
        showZeroPad = true;
      }
    } else {
      display.print(42, true);  // Shows "0042"
      Serial.println("Displaying: 0042 (zero-padded)");
      showZeroPad = false;
    }
  }
}
