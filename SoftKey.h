#ifndef _SOFTKEY
#define _SOFTKEY

#include <Adafruit_ILI9341.h>
#include <functional>
#include "KeyMap.h"

class SoftKey
{
  private:
// Coordinates for where the key is displayed on the screen
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;

// What letter and where should the letter be placed
    char keyValue;
    unsigned char getRow(KeyMap k) { return (int)k >> 4; };
    unsigned char getColumn(KeyMap k) { return (int)k - (((int)k >> 4) * 16); };

    uint16_t text_x;
    uint16_t text_y;

    bool isUpper;
    char upperValue;

    KeyMap keyMap;
// Colors
    uint8_t borderColor;
    uint8_t textColor;
    uint8_t flickerColor;
    uint8_t fillColor;

  public:
//    SoftKey() {};

    SoftKey(Adafruit_ILI9341 *, uint16_t, uint16_t, uint16_t, uint16_t, char);

// getters
    uint16_t getX() { return x; };
    uint16_t getY() { return y; };
    uint16_t getHeight() { return h; };
    uint16_t getWidth() { return w; };
    uint16_t getTextX() { return text_x; };
    uint16_t getTextY() { return text_y; };
    uint8_t getFillColor() { return fillColor; };
    uint8_t getBorderColor() { return borderColor; };
    uint8_t getTextColor() { return textColor; };
    uint8_t getFlickerColor() { return flickerColor; };
    char getKeyValue() { return keyValue; };

// setters
    void setBorderColor(uint16_t c) { borderColor = c; };
    void setTextColor(uint16_t c) { textColor = c; };
    void setFlickerColor(uint16_t c) { flickerColor = c; };
    void setFillColor(uint16_t c) { fillColor = c; };

    void setUpperValue(unsigned char c) { upperValue = c; };
    void setUppercase() { isUpper = true; };
    void setLowercase() { isUpper = false; };

    bool touched(uint16_t, uint16_t);

};

#endif
