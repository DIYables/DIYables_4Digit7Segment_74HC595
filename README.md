## 74HC595 4-Digit 7-Segment Display Library for Arduino - DIYables_4Digit7Segment_74HC595
This library is designed for Arduino, ESP32, ESP8266... to control the 74HC595 4-Digit 7-Segment Display LED module, which has 4 dots.


![74HC595 4-Digit 7-Segment Display Module](https://arduinogetstarted.com/images/tutorial/74hc595-4-digit-7-segment-display-pinout.jpg)



Product Link
----------------------------
[74HC595 4-Digit 7-Segment Display Module](https://diyables.io/products/4-digit-7-segment-display-led-74hc595-driver-with-4-dots)


Features
----------------------------
* **High-Level**: Displaying Integer with the zero-padding option, supporting the negative number
* **High-Level**: Displaying Float with the decimal place, zero-padding options, supporting the negative number
* **Low-Level**: Displaying numeric characters digit-by-digit
* **Low-Level**: Displaying non-numeric characters digit-by-digit, including:
  * \- (dash)
  * _ (underscore)
  * ° (degree)
  * C
  * E
  * F
* Low-Level: Displaying dot (decimal place) digit-by-digit


Available Functions
----------------------------
* DIYables_4Digit7Segment_74HC595(int sclk, int rclk, int dio);
* void printInt(int number, bool zero_padding);
* void printFloat(float number, int decimal_place, bool zero_padding);
* void clear();
* void setDot(int pos);
* void setNumber(int pos, int value);
* void setChar(int pos, SegChars value);
* void show();
* void loop();
 

Available Examples
----------------------------
* DisplayInteger
* DisplayFloat
* DisplayTemperature



References
----------------------------
* [DIYables_4Digit7Segment_74HC595 Library Reference](https://arduinogetstarted.com/reference/library/diyables-4digit7segment-74hc595-library)


Tutorials
----------------------------

* [Arduino - 74HC595 4-Digit 7-Segment Display](https://arduinogetstarted.com/tutorials/arduino-74hc595-4-digit-7-segment-display)
* [Arduino Uno R4 - 74HC595 4-Digit 7-Segment Display](https://newbiely.com/tutorials/arduino-uno-r4/arduino-uno-r4-74hc595-4-digit-7-segment-display)
* [Arduino Nano - 74HC595 4-Digit 7-Segment Display](https://newbiely.com/tutorials/arduino-nano/arduino-nano-74hc595-4-digit-7-segment-display)
* [Arduino Nano 33 IoT - 74HC595 4-Digit 7-Segment Display](https://newbiely.com/tutorials/arduino-nano-iot/arduino-nano-33-iot-74hc595-4-digit-7-segment-display)
* [Arduino Nano ESP32 - 74HC595 4-Digit 7-Segment Display](https://newbiely.com/tutorials/arduino-nano-esp32/arduino-nano-esp32-74hc595-4-digit-7-segment-display)
* [Arduino MKR WiFi 1010 - 74HC595 4-Digit 7-Segment Display](https://newbiely.com/tutorials/arduino-mkr/arduino-mkr-wifi-1010-74hc595-4-digit-7-segment-display)
* [Arduino Mega - 74HC595 4-Digit 7-Segment Display](https://newbiely.com/tutorials/arduino-mega/arduino-mega-74hc595-4-digit-7-segment-display)
* [ESP32 - 74HC595 4-Digit 7-Segment Display](https://esp32io.com/tutorials/esp32-74hc595-4-digit-7-segment-display)
* [ESP8266 - 74HC595 4-Digit 7-Segment Display](https://newbiely.com/tutorials/esp8266/esp8266-74hc595-4-digit-7-segment-display)


Tested Hardware
----------------------------

| Board                   | Tested |
|-------------------------|:------:|
| Arduino Uno R3          |   ✅   |
| [DIYables STEM V3 *(works like Arduino Uno R3)*](https://diyables.io/products/diyables-stem-v3-fully-compatible-with-arduino-uno-r3) |   ✅   |
| Arduino Uno R4 WiFi     |   ✅   |
| [DIYables STEM V4 IoT *(works like Arduino Uno R4 WiFi)*](https://diyables.io/products/diyables-stem-v4-iot-fully-compatible-with-arduino-uno-r4-wifi) |   ✅   |
| [DIYables STEM V4B IoT *(works like Arduino Uno R4 WiFi)*](https://diyables.io/products/diyables-stem-v4b-iot-development-board-compatible-with-arduino-uno-r4-wifi-ra4m1-32-bit-arm-cortex-m4-with-esp32-s3-wifi-bluetooth-usb-c-for-learning-prototyping-education) |   ✅   |
| Arduino Uno R4 Minima   |   ✅   |
| [DIYables STEM V4 Edu *(works like Arduino Uno R4 Minima)*](https://diyables.io/stem-v4-edu) |   ✅   |
| Arduino Mega            |   ✅   |
| [DIYables MEGA2560 R3 *(works like Arduino Mega 2560 Rev3)*](https://diyables.io/atmega2560-board) |   ✅   |
| Arduino Due             |   ✅    |
| Arduino Giga            |   ✅    |
| [DIYables ESP32 Development Board](https://diyables.io/esp32-board) |   ✅   |
| [DIYables ESP32 S3, Uno-form factor](https://diyables.io/products/esp32-s3-development-board-with-esp32-s3-wroom-1-n16r8-wifi-bluetooth-uno-compatible-form-factor-works-with-arduino-ide) |   ✅   |
| Other boards            |   Not yet, expected to work    |