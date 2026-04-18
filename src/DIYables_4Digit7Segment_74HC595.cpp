#include "DIYables_4Digit7Segment_74HC595.h"

// Character map: maps ASCII characters to 7-segment patterns (active HIGH)
// Segment bit mapping: DP G F E D C B A
static const uint8_t CHAR_MAP[] PROGMEM = {
    // Index 0-9: digits '0'-'9'
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
};

// Digit select patterns: position 0 = leftmost, position 3 = rightmost
// For 74HC595 module: bit3 = leftmost digit, bit0 = rightmost digit
static const uint8_t DIGIT_PATTERNS[NUM_DIGITS] = {0x08, 0x04, 0x02, 0x01};

uint8_t DIYables_4Digit7Segment_74HC595::_charToSegments(char ch) {
    if (ch >= '0' && ch <= '9') {
        return pgm_read_byte(&CHAR_MAP[ch - '0']);
    }
    switch (ch) {
        case 'A': case 'a': return 0x77;
        case 'B': case 'b': return 0x7C;
        case 'C':           return 0x39;
        case 'c':           return 0x58;
        case 'D': case 'd': return 0x5E;
        case 'E': case 'e': return 0x79;
        case 'F': case 'f': return 0x71;
        case 'G':           return 0x3D;
        case 'g':           return 0x6F;
        case 'H':           return 0x76;
        case 'h':           return 0x74;
        case 'I':           return 0x06;
        case 'i':           return 0x04;
        case 'J': case 'j': return 0x1E;
        case 'L': case 'l': return 0x38;
        case 'N':           return 0x37;
        case 'n':           return 0x54;
        case 'O':           return 0x3F;
        case 'o':           return 0x5C;
        case 'P': case 'p': return 0x73;
        case 'R':           return 0x77;
        case 'r':           return 0x50;
        case 'S': case 's': return 0x6D;
        case 'T': case 't': return 0x78;
        case 'U':           return 0x3E;
        case 'u':           return 0x1C;
        case 'Y': case 'y': return 0x6E;
        case ' ':           return 0x00;
        case '-':           return 0x40;
        case '_':           return 0x08;
        case DEGREE_CHAR:   return 0x63;
        default:            return 0x00;
    }
}

DIYables_4Digit7Segment_74HC595::DIYables_4Digit7Segment_74HC595(int sclkPin, int rclkPin, int dioPin, bool commonAnode) {
    _sclkPin = sclkPin;
    _rclkPin = rclkPin;
    _dioPin = dioPin;
    _commonAnode = commonAnode;
    _enabled = true;
    _currentDigit = 0;
    _lastRefresh = 0;
    for (int i = 0; i < NUM_DIGITS; i++) {
        _buffer[i] = 0x00;
        _dots[i] = false;
    }
}

void DIYables_4Digit7Segment_74HC595::begin() {
    pinMode(_sclkPin, OUTPUT);
    pinMode(_rclkPin, OUTPUT);
    pinMode(_dioPin, OUTPUT);
    digitalWrite(_sclkPin, LOW);
    digitalWrite(_rclkPin, LOW);
    digitalWrite(_dioPin, LOW);
}

void DIYables_4Digit7Segment_74HC595::_shiftOut(uint8_t data) {
    for (int i = 7; i >= 0; i--) {
        digitalWrite(_dioPin, (data >> i) & 1);
        digitalWrite(_sclkPin, LOW);
        digitalWrite(_sclkPin, HIGH);
    }
}

void DIYables_4Digit7Segment_74HC595::_latch() {
    digitalWrite(_rclkPin, LOW);
    digitalWrite(_rclkPin, HIGH);
}

void DIYables_4Digit7Segment_74HC595::_writeDigit(uint8_t position, uint8_t segments) {
    uint8_t segData;
    if (_commonAnode) {
        segData = (~segments) & 0xFF;
    } else {
        segData = segments & 0xFF;
    }
    uint8_t digitSelect = DIGIT_PATTERNS[position];
    _shiftOut(segData);
    _shiftOut(digitSelect);
    _latch();
}

void DIYables_4Digit7Segment_74HC595::loop() {
    if (!_enabled) return;

    unsigned long now = millis();
    if (now - _lastRefresh >= REFRESH_INTERVAL_MS) {
        _lastRefresh = now;
        uint8_t segments = _buffer[_currentDigit];
        if (_dots[_currentDigit]) {
            segments |= SEG_DP;
        }
        _writeDigit(_currentDigit, segments);
        _currentDigit = (_currentDigit + 1) % NUM_DIGITS;
    }
}

void DIYables_4Digit7Segment_74HC595::clear() {
    for (int i = 0; i < NUM_DIGITS; i++) {
        _buffer[i] = 0x00;
        _dots[i] = false;
    }
}

// --- Primary API ---

void DIYables_4Digit7Segment_74HC595::print(int value, bool zeroPad) {
    _printInt(value, zeroPad);
}

void DIYables_4Digit7Segment_74HC595::print(double value, int decimalPlaces, bool zeroPad) {
    _printFloat(value, decimalPlaces, zeroPad);
}

void DIYables_4Digit7Segment_74HC595::print(const char* text) {
    _printStr(text);
}

void DIYables_4Digit7Segment_74HC595::printTemperature(int temperature, char unit) {
    clear();
    bool negative = temperature < 0;
    int absTemp = abs(temperature);

    if (negative) {
        if (absTemp > 9) {
            _buffer[0] = _charToSegments('-');
            _buffer[1] = _charToSegments('0' + (absTemp / 10));
            _buffer[2] = _charToSegments('0' + (absTemp % 10));
            _buffer[3] = _charToSegments(DEGREE_CHAR);
        } else {
            _buffer[0] = _charToSegments('-');
            _buffer[1] = _charToSegments('0' + absTemp);
            _buffer[2] = _charToSegments(DEGREE_CHAR);
            _buffer[3] = _charToSegments(unit);
        }
    } else {
        if (absTemp >= 100) {
            _buffer[0] = _charToSegments('0' + ((absTemp / 100) % 10));
            _buffer[1] = _charToSegments('0' + ((absTemp / 10) % 10));
            _buffer[2] = _charToSegments('0' + (absTemp % 10));
            _buffer[3] = _charToSegments(DEGREE_CHAR);
        } else if (absTemp >= 10) {
            _buffer[0] = _charToSegments('0' + (absTemp / 10));
            _buffer[1] = _charToSegments('0' + (absTemp % 10));
            _buffer[2] = _charToSegments(DEGREE_CHAR);
            _buffer[3] = _charToSegments(unit);
        } else {
            _buffer[0] = 0x00;
            _buffer[1] = _charToSegments('0' + absTemp);
            _buffer[2] = _charToSegments(DEGREE_CHAR);
            _buffer[3] = _charToSegments(unit);
        }
    }
}

void DIYables_4Digit7Segment_74HC595::printTime(int hours, int minutes, bool colon) {
    clear();
    _buffer[0] = _charToSegments('0' + (hours / 10));
    _buffer[1] = _charToSegments('0' + (hours % 10));
    _buffer[2] = _charToSegments('0' + (minutes / 10));
    _buffer[3] = _charToSegments('0' + (minutes % 10));
    if (colon) {
        _dots[1] = true;
    }
}

void DIYables_4Digit7Segment_74HC595::off() {
    _enabled = false;
    if (_commonAnode) {
        _shiftOut(0xFF);
        _shiftOut(0x00);
    } else {
        _shiftOut(0x00);
        _shiftOut(0x00);
    }
    _latch();
}

void DIYables_4Digit7Segment_74HC595::on() {
    _enabled = true;
}

void DIYables_4Digit7Segment_74HC595::delay(unsigned long ms) {
    unsigned long start = millis();
    while (millis() - start < ms) {
        loop();
    }
}

void DIYables_4Digit7Segment_74HC595::yield() {
    loop();
}

// --- Low-level API ---

void DIYables_4Digit7Segment_74HC595::setDot(int position, bool state) {
    if (position >= 0 && position <= 3) {
        _dots[position] = state;
    }
}

void DIYables_4Digit7Segment_74HC595::setChar(int position, char ch) {
    if (position >= 0 && position <= 3) {
        _buffer[position] = _charToSegments(ch);
    }
}

void DIYables_4Digit7Segment_74HC595::setSegments(int position, uint8_t segments) {
    if (position >= 0 && position <= 3) {
        _buffer[position] = segments & 0x7F;
    }
}

void DIYables_4Digit7Segment_74HC595::setNumber(int position, int number) {
    if (position >= 0 && position <= 3 && number >= 0 && number <= 9) {
        _buffer[position] = _charToSegments('0' + number);
    }
}

// --- Internal methods ---

void DIYables_4Digit7Segment_74HC595::_printInt(int number, bool zeroPad) {
    clear();

    if (number < -999 || number > 9999) {
        _buffer[1] = _charToSegments('E');
        _buffer[2] = _charToSegments('r');
        _buffer[3] = _charToSegments('r');
        return;
    }

    bool negative = number < 0;
    if (negative) {
        number = -number;
    }

    // Extract digits
    int digits[4];
    int count = 0;
    if (number == 0) {
        digits[0] = 0;
        count = 1;
    } else {
        int temp = number;
        while (temp > 0) {
            digits[count++] = temp % 10;
            temp /= 10;
        }
        // Reverse
        for (int i = 0; i < count / 2; i++) {
            int swap = digits[i];
            digits[i] = digits[count - 1 - i];
            digits[count - 1 - i] = swap;
        }
    }

    int maxDigits = negative ? 3 : 4;

    // Zero padding
    if (zeroPad) {
        while (count < maxDigits) {
            // Shift right and insert 0
            for (int i = count; i > 0; i--) {
                digits[i] = digits[i - 1];
            }
            digits[0] = 0;
            count++;
        }
    }

    int startPos = 4 - count;
    if (negative) {
        startPos--;
    }

    if (negative) {
        _buffer[startPos] = _charToSegments('-');
        startPos++;
    }

    for (int i = 0; i < count; i++) {
        int pos = startPos + i;
        if (pos >= 0 && pos <= 3) {
            _buffer[pos] = _charToSegments('0' + digits[i]);
        }
    }
}

void DIYables_4Digit7Segment_74HC595::_printFloat(double number, int decimalPlaces, bool zeroPad) {
    clear();

    bool negative = number < 0;
    if (negative) {
        number = -number;
    }

    int availableDigits = negative ? 3 : 4;

    if (decimalPlaces < 0) {
        // Auto decimal places
        int intPart = (int)number;
        int intDigits = 0;
        if (intPart == 0) {
            intDigits = 1;
        } else {
            int temp = intPart;
            while (temp > 0) {
                intDigits++;
                temp /= 10;
            }
        }
        decimalPlaces = availableDigits - intDigits;
        if (decimalPlaces < 0) decimalPlaces = 0;
        if (decimalPlaces > 3) decimalPlaces = 3;
    }

    // Round to desired decimal places
    float rounded;
    if (decimalPlaces > 0) {
        float factor = 1.0;
        for (int i = 0; i < decimalPlaces; i++) factor *= 10.0;
        rounded = ((int)(number * factor + 0.5)) / factor;
    } else {
        rounded = (int)(number + 0.5);
    }

    int intPart = (int)rounded;
    long factor = 1;
    for (int i = 0; i < decimalPlaces; i++) factor *= 10;
    int fracPart = (int)((rounded - intPart) * factor + 0.5);

    if (fracPart >= factor) {
        intPart++;
        fracPart = 0;
    }

    // Build digit string
    char fullStr[8];
    int idx = 0;

    if (negative) {
        fullStr[idx++] = '-';
    }

    // Integer part digits
    char intStr[6];
    int intIdx = 0;
    if (intPart == 0) {
        intStr[intIdx++] = '0';
    } else {
        int temp = intPart;
        while (temp > 0) {
            intStr[intIdx++] = '0' + (temp % 10);
            temp /= 10;
        }
        // Reverse
        for (int i = 0; i < intIdx / 2; i++) {
            char swap = intStr[i];
            intStr[i] = intStr[intIdx - 1 - i];
            intStr[intIdx - 1 - i] = swap;
        }
    }

    // Fractional part digits
    char fracStr[6];
    int fracIdx = 0;
    if (decimalPlaces > 0) {
        int temp = fracPart;
        for (int i = 0; i < decimalPlaces; i++) {
            fracStr[fracIdx++] = '0' + (temp % 10);
            temp /= 10;
        }
        // Reverse
        for (int i = 0; i < fracIdx / 2; i++) {
            char swap = fracStr[i];
            fracStr[i] = fracStr[fracIdx - 1 - i];
            fracStr[fracIdx - 1 - i] = swap;
        }
    }

    int totalDigits = (negative ? 1 : 0) + intIdx + fracIdx;
    if (totalDigits > 4) {
        _buffer[1] = _charToSegments('E');
        _buffer[2] = _charToSegments('r');
        _buffer[3] = _charToSegments('r');
        return;
    }

    // Copy int digits
    for (int i = 0; i < intIdx; i++) {
        fullStr[idx++] = intStr[i];
    }
    // Copy frac digits
    for (int i = 0; i < fracIdx; i++) {
        fullStr[idx++] = fracStr[i];
    }

    // Zero padding
    if (zeroPad) {
        int needed = 4 - idx;
        if (negative) {
            // Insert zeros after the minus sign
            for (int i = idx - 1; i >= 1; i--) {
                fullStr[i + needed] = fullStr[i];
            }
            for (int i = 0; i < needed; i++) {
                fullStr[1 + i] = '0';
            }
        } else {
            for (int i = idx - 1; i >= 0; i--) {
                fullStr[i + needed] = fullStr[i];
            }
            for (int i = 0; i < needed; i++) {
                fullStr[i] = '0';
            }
        }
        idx += needed;
    }

    int startPos = 4 - idx;
    for (int i = 0; i < idx; i++) {
        int pos = startPos + i;
        if (pos >= 0 && pos <= 3) {
            _buffer[pos] = _charToSegments(fullStr[i]);
        }
    }

    // Set decimal point
    if (decimalPlaces > 0) {
        int dpPos = 4 - decimalPlaces - 1;
        if (dpPos >= 0 && dpPos <= 3) {
            _dots[dpPos] = true;
        }
    }
}

void DIYables_4Digit7Segment_74HC595::_printStr(const char* text) {
    clear();

    int pos = 0;
    int i = 0;
    while (text[i] != '\0' && pos < NUM_DIGITS) {
        char ch = text[i];
        if (ch == '.') {
            if (pos > 0) {
                _dots[pos - 1] = true;
            }
            i++;
            continue;
        }

        _buffer[pos] = _charToSegments(ch);
        i++;

        if (text[i] == '.') {
            _dots[pos] = true;
            i++;
        }

        pos++;
    }
}
