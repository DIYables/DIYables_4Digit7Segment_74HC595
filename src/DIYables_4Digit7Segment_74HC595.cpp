/*
   Copyright (c) 2023, DIYables.io. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

   - Neither the name of the DIYables.io nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY DIYABLES.IO "AS IS" AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL DIYABLES.IO BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
   IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#include <DIYables_4Digit7Segment_74HC595.h>

const byte DIYables_4Digit7Segment_74HC595::digitPatterns[16] = {
  B11000000,  // 0
  B11111001,  // 1
  B10100100,  // 2
  B10110000,  // 3
  B10011001,  // 4
  B10010010,  // 5
  B10000010,  // 6
  B11111000,  // 7
  B10000000,  // 8
  B10010000,  // 9
  B10111111,  // - (dash)
  B11110111,  // _ (underscore)
  B11000110,  // C
  B10000110,  // E
  B10001110,  // F
  B10011100   // ° (degree)
};


DIYables_4Digit7Segment_74HC595::DIYables_4Digit7Segment_74HC595(int sclk, int rclk, int dio) {
  _sclk = sclk;
  _rclk = rclk;
  _dio  = dio;

  for (int i = 0; i < 4; i++) {
    _digit_sets[i]   = (byte)SEG7_OFF;
    _digit_values[i] = (byte)SEG7_OFF;
  }
  _digit_dots      = 0x00;

  pinMode(_sclk, OUTPUT);
  pinMode(_rclk, OUTPUT);
  pinMode(_dio,  OUTPUT);
}

void DIYables_4Digit7Segment_74HC595::clear() {
  _digit_dots = 0x00;
  for (int i = 0; i < 4; i++)
    _digit_sets[i] = 0xFF;
}

void DIYables_4Digit7Segment_74HC595::setDot(int pos) {
  if (pos < 1 || pos > 4)
    return;

  _digit_dots |= 1 << (pos - 1);
}

void DIYables_4Digit7Segment_74HC595::setNumber(int pos, int value) {
  if (pos < 1 || pos > 4)
    return;

  if (value < 0 || pos > 9)
    return;

  _digit_sets[pos - 1] = digitPatterns[value];
}

void DIYables_4Digit7Segment_74HC595::setChar(int pos, SegChars value) {
  if (pos < 1 || pos > 4)
    return;

  switch (value) {
    case SegChars::DASH:
      _digit_sets[pos - 1] = digitPatterns[10];
      break;

    case SegChars::UNDERSCORE:
      _digit_sets[pos - 1] = digitPatterns[11];
      break;

    case SegChars::C:
      _digit_sets[pos - 1] = digitPatterns[12];
      break;

    case SegChars::E:
      _digit_sets[pos - 1] = digitPatterns[13];
      break;

    case SegChars::F:
      _digit_sets[pos - 1] = digitPatterns[14];
      break;

    case SegChars::DEGREE:
      _digit_sets[pos - 1] = digitPatterns[15];
      break;
  }
}

void DIYables_4Digit7Segment_74HC595::show() {
  for (int i = 0; i < 4; i++)
    _digit_values[i] = _digit_sets[i];
}

void DIYables_4Digit7Segment_74HC595::loop() {
  for (int i = 0; i < 4; i++) {
    int digit = 0x08 >> i;
    int value = _digit_values[i];

    if (_digit_dots & (1 << i))
      value &= 0x7F;

    this->shift(value);
    this->shift(digit);
    digitalWrite(_rclk, LOW);
    digitalWrite(_rclk, HIGH);
  }
}

void DIYables_4Digit7Segment_74HC595::shift(byte value) {
  for (byte i = 8; i >= 1; i--) {
    if (value & 0x80)
      digitalWrite(_dio, HIGH);
    else
      digitalWrite(_dio, LOW);

    value <<= 1;
    digitalWrite(_sclk, LOW);
    digitalWrite(_sclk, HIGH);
  }
}

void DIYables_4Digit7Segment_74HC595::setInt(int number, bool zero_padding) {
  if (number > 9999) // trim
    number %=  10000;
  else if (number < -999) // trim
    number %= 1000;

  int digit_num = 0;
  int number_abs = abs(number);

  if (number_abs <= 9999 && number_abs >= 1009)
    digit_num = 4;
  else  if (number_abs <= 999 && number_abs >= 100)
    digit_num = 3;
  else if (number_abs <= 99 && number_abs >= 10)
    digit_num = 2;
  else if (number_abs <= 9 && number_abs >= 0)
    digit_num = 1;

  if (number < 0)
    digit_num++;

  int denominator = 10000;
  for (int pos = 1; pos <= 4; pos++) {
    denominator /= 10;
    if (!zero_padding && pos <= (4 - digit_num))
      continue;

    if (number < 0) {
      setChar(pos, SegChars::DASH); // set - at the 1st digit
      number *= -1;
    } else {
      int digit = number / denominator;
      number = number % denominator;
      setNumber(pos, digit);
      Serial.println(digit);
    }
  }
}

void DIYables_4Digit7Segment_74HC595::printInt(int number, bool zero_padding) {
  clear();
  setInt(number, zero_padding);
  show(); // show on the display
}

void DIYables_4Digit7Segment_74HC595::printFloat(float number, int decimal_place, bool zero_padding) {
  clear();
  if (decimal_place > 3)
    decimal_place = 3;
  else if (decimal_place < 0)
    decimal_place = 0;

  if (decimal_place != 0)
    setDot(4 - decimal_place);

  int integer = number * pow(10, decimal_place);

  setInt(integer, zero_padding);
  show(); // show on the display
}
