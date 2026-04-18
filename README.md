# DIYables_4Digit7Segment_74HC595 - Arduino Library for 4-Digit 7-Segment Display with 74HC595

Arduino library for 4-digit 7-segment LED display driven by 74HC595 shift register. Supports 4 decimal point dots.

![4-Digit 7-Segment Display 74HC595](https://arduinogetstarted.com/images/tutorial/74hc595-4-digit-7-segment-display-pinout.jpg)

## Product

* [DIYables 4-Digit 7-Segment Display LED 74HC595 Driver with 4 Dots](https://diyables.io/products/4-digit-7-segment-display-led-74hc595-driver-with-4-dots)

## Tested Hardware

| Board                   | Tested |
|-------------------------|:------:|
| Arduino Uno R3          |   ✅   |
| Arduino Uno R4 WiFi     |   ✅   |
| Arduino Uno R4 Minima   |   ✅   |
| Arduino Mega            |   ✅   |
| Arduino Giga            |   ✅   |
| Arduino Due             |   ✅   |
| [DIYables STEM V4 IoT *(works like Arduino Uno R4 WiFi)*](https://diyables.io/products/diyables-stem-v4-iot-fully-compatible-with-arduino-uno-r4-wifi) |   ✅   |
| [DIYables STEM V4B IoT *(works like Arduino Uno R4 WiFi)*](https://diyables.io/products/diyables-stem-v4b-iot-development-board-compatible-with-arduino-uno-r4-wifi-ra4m1-32-bit-arm-cortex-m4-with-esp32-s3-wifi-bluetooth-usb-c-for-learning-prototyping-education) |   ✅   |
| [DIYables STEM V3 *(works like Arduino Uno R3)*](https://diyables.io/products/diyables-stem-v3-fully-compatible-with-arduino-uno-r3) |   ✅   |
| [DIYables STEM V4B Edu *(works like Arduino Uno R4 Minima)*](https://diyables.io/stem-v4-edu) |   ✅   |
| [DIYables MEGA2560 R3 *(works like Arduino Mega 2560 Rev3)*](https://diyables.io/atmega2560-board) |   ✅   |
| [DIYables Nano R3 *(works like Arduino Nano R3)*](https://diyables.io/nano-board) |   ✅   |
| [DIYables ESP32 Development Board](https://diyables.io/esp32-board) |   ✅   |
| [DIYables ESP32 S3, Uno-form factor](https://diyables.io/products/esp32-s3-development-board-with-esp32-s3-wroom-1-n16r8-wifi-bluetooth-uno-compatible-form-factor-works-with-arduino-ide) |   ✅   |
| Other boards            |   Not yet, expected to work    |

## Features

- Display integers (-999 to 9999)
- Display floats with automatic or manual decimal places
- Display alphabetic characters (A-U, Y)
- Display special characters (degree, dash, underscore)
- Zero-padding support
- Temperature display with degree symbol (C / F)
- Time display (HH.MM) with blinking dot separator
- Individual dot/decimal point control for all 4 digits
- String display with inline dots
- Common anode and common cathode support
- Cross-platform: works with all Arduino-compatible boards (architectures=*)

## ⚠️ Important: Keeping the Display Alive

This display uses software multiplexing — `display.loop()` must run frequently to keep the digits visible. **Do NOT use the standard `delay()` function**, as it blocks the refresh and causes the display to go blank or flicker.

The library provides two methods to solve this:

- **`display.delay(ms)`** — Drop-in replacement for `delay()`. Internally keeps calling `loop()` while waiting, so the display stays refreshed. Simply swap `delay(1000)` with `display.delay(1000)`.
- **`display.yield()`** — Single-call refresh. Sprinkle this inside long processing loops (e.g. `for` loops with heavy computation) to keep the display alive between iterations.

```cpp
// Instead of delay(2000):
display.delay(2000);  // Display stays on during the wait

// Inside a long-running loop:
for (int i = 0; i < 10000; i++) {
  heavyComputation();
  display.yield();  // Quick refresh to keep the display alive
}
```

## Hardware Required

- An Arduino board (or any compatible board)
- A 4-digit 7-segment display module with 74HC595 (with 4 dots)
- Jumper wires

## Pin Mapping (74HC595 Module)

| Function | Pin |
|---|---|
| SCLK (SH_CP) | Serial clock |
| RCLK (ST_CP) | Register clock / latch |
| DIO (DS) | Data input |
| VCC | 3.3V or 5V |
| GND | Ground |

## Quick Start

```cpp
#include <DIYables_4Digit7Segment_74HC595.h>

#define SCLK_PIN 7
#define RCLK_PIN 6
#define DIO_PIN  5

DIYables_4Digit7Segment_74HC595 display(SCLK_PIN, RCLK_PIN, DIO_PIN);

void setup() {
  display.begin();
  display.print(1234);
}

void loop() {
  display.loop();  // Must be called frequently to refresh the display
}
```

## Examples

- **Integer**: Display integers with optional zero-padding
- **Float**: Display floats with auto/manual decimal places
- **TextAndDegree**: Display text, degree symbol, and temperature
- **Time**: Display time with blinking dot separator
- **Blink**: Blink integers, floats, and text using off()/on()

## API Reference

See [DIYables_4Digit7Segment_74HC595 Library Reference](https://newbiely.com/library-references/diyables-4-digit-7-segment-74hc595-library-reference) for the complete API documentation including all constructors, methods, and constants.

## Tutorials

- [Arduino - 4-Digit 7-Segment Display 74HC595](https://arduinogetstarted.com/tutorials/arduino-74hc595-4-digit-7-segment-display)
- [Arduino Uno R4 - 4-Digit 7-Segment Display 74HC595](https://newbiely.com/tutorials/arduino-uno-r4/arduino-uno-r4-74hc595-4-digit-7-segment-display)
- [Arduino Mega - 4-Digit 7-Segment Display 74HC595](https://newbiely.com/tutorials/arduino-mega/arduino-mega-74hc595-4-digit-7-segment-display)
- [Arduino Giga R1 WiFi - 4-Digit 7-Segment Display 74HC595](https://newbiely.com/tutorials/arduino-giga/arduino-giga-r1-wifi-74hc595-4-digit-7-segment-display)
- [Arduino Nano - 4-Digit 7-Segment Display 74HC595](https://newbiely.com/tutorials/arduino-nano/arduino-nano-74hc595-4-digit-7-segment-display)
- [Arduino Nano ESP32 - 4-Digit 7-Segment Display 74HC595](https://newbiely.com/tutorials/arduino-nano-esp32/arduino-nano-esp32-74hc595-4-digit-7-segment-display)
- [Arduino Nano 33 IoT - 4-Digit 7-Segment Display 74HC595](https://newbiely.com/tutorials/arduino-nano-iot/arduino-nano-33-iot-74hc595-4-digit-7-segment-display)
- [Arduino MKR WiFi 1010 - 4-Digit 7-Segment Display 74HC595](https://newbiely.com/tutorials/arduino-mkr/arduino-mkr-wifi-1010-74hc595-4-digit-7-segment-display)
- [ESP8266 - 4-Digit 7-Segment Display 74HC595](https://newbiely.com/tutorials/esp8266/esp8266-74hc595-4-digit-7-segment-display)
- [ESP32 - 4-Digit 7-Segment Display 74HC595](https://esp32io.com/tutorials/esp32-74hc595-4-digit-7-segment-display)

## License

BSD. See [license.txt](license.txt).
