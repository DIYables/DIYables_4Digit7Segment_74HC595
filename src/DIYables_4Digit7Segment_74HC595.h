#ifndef DIYables_4Digit7Segment_74HC595_h
#define DIYables_4Digit7Segment_74HC595_h

#include <Arduino.h>

// Segment bit mapping: DP G F E D C B A
// Bit positions:        7  6 5 4 3 2 1 0

#define SEG_A  0x01
#define SEG_B  0x02
#define SEG_C  0x04
#define SEG_D  0x08
#define SEG_E  0x10
#define SEG_F  0x20
#define SEG_G  0x40
#define SEG_DP 0x80

// Special character code for degree symbol
#define DEGREE_CHAR '\x07'

// Number of digits
#define NUM_DIGITS 4

// Refresh interval in milliseconds (per digit)
#define REFRESH_INTERVAL_MS 2

class DIYables_4Digit7Segment_74HC595 {
public:
    DIYables_4Digit7Segment_74HC595(int sclkPin, int rclkPin, int dioPin, bool commonAnode = true);

    void begin();
    void loop();

    // Primary API
    void print(int value, bool zeroPad = false);
    void print(double value, int decimalPlaces = -1, bool zeroPad = false);
    void print(const char* text);
    void printTemperature(int temperature, char unit = 'C');
    void printTime(int hours, int minutes, bool colon = true);

    void clear();
    void off();
    void on();

    // Display-aware blocking helpers
    void delay(unsigned long ms);
    void yield();

    // Low-level API
    void setDot(int position, bool state = true);
    void setChar(int position, char ch);
    void setSegments(int position, uint8_t segments);
    void setNumber(int position, int number);

private:
    int _sclkPin;
    int _rclkPin;
    int _dioPin;
    bool _commonAnode;
    bool _enabled;

    uint8_t _buffer[NUM_DIGITS];
    bool _dots[NUM_DIGITS];
    uint8_t _currentDigit;
    unsigned long _lastRefresh;

    void _shiftOut(uint8_t data);
    void _latch();
    void _writeDigit(uint8_t position, uint8_t segments);
    void _printInt(int number, bool zeroPad);
    void _printFloat(double number, int decimalPlaces, bool zeroPad);
    void _printStr(const char* text);

    static uint8_t _charToSegments(char ch);
};

#endif
