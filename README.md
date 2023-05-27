## 74HC595 4-Digit 7-Segment Display Library for Arduino - DIYables_4Digit7Segment_74HC595
This library is designed for Arduino, ESP32, ESP8266... to control the 74HC595 4-Digit 7-Segment Display LED module, which has 4 dots.


![74HC595 4-Digit 7-Segment Display Module](https://arduinogetstarted.com/images/tutorial/74hc595-4-digit-7-segment-display-pinout.jpg)


Product Link: [74HC595 4-Digit 7-Segment Display Module](https://diyables.io/products/4-digit-7-segment-display-led-74hc595-driver-with-4-dots)


Features
----------------------------
* **High-Level**: Displaying Integer with the zero-padding option, supporting the negative number
* **High-Level**: Displaying Float with the decimal place, zero-padding options, supporting the negative number
* **Low-Level**: Displaying numeric characters digit-by-digit
* **Low-Level**: Displaying non-numeric characters digit-by-digit, including:
  * - (dash)
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
* [ESP32 - 74HC595 4-Digit 7-Segment Display](https://esp32io.com/tutorials/esp32-74hc595-4-digit-7-segment-display)
* [ESP8266 - 74HC595 4-Digit 7-Segment Display](https://newbiely.com/tutorials/esp8266/esp8266-74hc595-4-digit-7-segment-display)

