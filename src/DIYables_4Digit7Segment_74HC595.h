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

#ifndef DIYables_4Digit7Segment_74HC595_h
#define DIYables_4Digit7Segment_74HC595_h

#include <Arduino.h>

#define SEG7_OFF 0xFF

enum class SegChars {
  DASH,
  UNDERSCORE,
  C,
  E,
  F,
  DEGREE
};

class DIYables_4Digit7Segment_74HC595
{
  private:
    int _sclk;
    int _rclk;
    int _dio;

    static const byte digitPatterns[16];

    byte _digit_sets[4];
    byte _digit_values[4];
    byte _digit_dots;

    void shift(byte value);
    void setInt(int number, bool zero_padding);

  public:
    DIYables_4Digit7Segment_74HC595(int sclk, int rclk, int dio);

    void clear();
    void setDot(int pos);
    void setNumber(int pos, int value);
    void setChar(int pos, SegChars value);
    void show();
    void loop();
    void printInt(int number, bool zero_padding);
    void printFloat(float number, int decimal_place, bool zero_padding);
};

#endif
