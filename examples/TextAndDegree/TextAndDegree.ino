/*
 * DIYables_4Digit7Segment_74HC595 - TextAndDegree Example
 *
 * Display text strings, special characters, and temperature on a 4-digit
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

const char* texts[] = {"HELP", "Hi", "COOL", "done"};
int textCount = 4;
int currentIndex = 0;
int phase = 0;
unsigned long lastChange = 0;

void setup() {
  Serial.begin(9600);
  display.begin();
  Serial.println("4-Digit 7-Segment 74HC595 - Text and Degree Example");
}

void loop() {
  display.loop();  // Must be called frequently to refresh the display

  if (millis() - lastChange >= 2000) {
    lastChange = millis();

    if (phase == 0) {
      // Display text strings
      display.print(texts[currentIndex]);
      Serial.print("Text: ");
      Serial.println(texts[currentIndex]);
      currentIndex++;
      if (currentIndex >= textCount) {
        currentIndex = 0;
        phase = 1;
      }
    } else if (phase == 1) {
      // Display temperature 25 degrees C
      display.printTemperature(25, 'C');
      Serial.println("Temperature: 25 C");
      phase = 2;
    } else if (phase == 2) {
      // Display temperature 72 degrees F
      display.printTemperature(72, 'F');
      Serial.println("Temperature: 72 F");
      phase = 3;
    } else if (phase == 3) {
      // Display degree symbol using string with DEGREE_CHAR constant
      char degStr[5];
      degStr[0] = '2';
      degStr[1] = '5';
      degStr[2] = DEGREE_CHAR;
      degStr[3] = 'C';
      degStr[4] = '\0';
      display.print(degStr);
      Serial.println("String with degree: 25 deg C");
      phase = 4;
    } else {
      // Display string with dots
      display.print("1.2.3.4");
      Serial.println("Dots: 1.2.3.4");
      phase = 0;
    }
  }
}
