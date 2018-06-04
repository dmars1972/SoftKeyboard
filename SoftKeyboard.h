#ifndef _SOFT_KEYBOARD
#define _SOFT_KEYBOARD

#include "Arduino.h"

#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <Adafruit_STMPE610.h>

#include "KeyMap.h"
#include "SoftKey.h"

class SoftKeyboard
{
  private:
// letters + numbers only here
    SoftKey *keys[29];

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;

    uint16_t minX;
    uint16_t maxX;
    uint16_t minY;
    uint16_t maxY;

//    Adafruit_ILI9341 *_tft;

  public:
    SoftKeyboard(Adafruit_ILI9341 *, Adafruit_STMPE610 *, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
};



#endif
