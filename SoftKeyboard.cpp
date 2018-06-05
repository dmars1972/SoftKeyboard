#include "SoftKeyboard.h"

SoftKeyboard::SoftKeyboard(
    Adafruit_ILI9341 *_tft, 
    Adafruit_STMPE610 *_spitouch,
    uint16_t xpos, 
    uint16_t ypos, 
    uint16_t width, 
    uint16_t height, 
    uint16_t touch_minx, 
    uint16_t touch_maxx, 
    uint16_t touch_miny, 
    uint16_t touch_maxy,
    String &retstr)
{
  unsigned char letter;
  int index;
  char str[64];

  memset(str, '\0', sizeof(str));

  x = xpos;
  y = ypos;
  w = width;
  h = height;
  minX = touch_minx;
  maxX = touch_maxx;
  minY = touch_miny;
  maxY = touch_maxy;

  _tft->fillScreen(ILI9341_BLACK);

  _tft->fillRoundRect(x, y, w, 35, 3, ILI9341_BLACK);
  _tft->drawRoundRect(x, y, w, 35, 3, ILI9341_CYAN);

  for(letter = 'a', index = 0; letter <= 'z'; ++letter, ++index)
    keys[index] = SoftKey(_tft, x, y+40, w, h, letter);

  keys[26] = SoftKey(_tft, x, y+40, w, h, '/');
  keys[27] = SoftKey(_tft, x, y+40, w, h, ']', 2);
  keys[28] = SoftKey(_tft, x, y+40, w, h, ' ', 6);

  for(letter = 0; letter < 29; letter++) {
      _tft->fillRoundRect(
          keys[letter].getX(),
          keys[letter].getY(),
          keys[letter].getWidth(),
          keys[letter].getHeight(),
          3,
          ILI9341_CYAN);

      _tft->drawRoundRect(
          keys[letter].getX(),
          keys[letter].getY(),
          keys[letter].getWidth(),
          keys[letter].getHeight(),
          3,
          ILI9341_DARKCYAN);

    if(isalpha(keys[letter].getKeyValue())) {
      _tft->drawChar(
          keys[letter].getTextX(), 
          keys[letter].getTextY(), 
          keys[letter].getKeyValue(), 
          ILI9341_BLACK, 
          ILI9341_CYAN, 
          1);
    } else {
      switch(keys[letter].getKeyValue()) {
        case ' ':
            break;
        case '/':
            drawBackspace(_tft, keys[letter]);
            break;
        case ']':
            drawEnter(_tft, keys[letter]);
            break;
      }
    }
  }

  do {
    _spitouch->getPoint();
  } while(!_spitouch->bufferEmpty());

  while(true) {
    TS_Point touch_p;
    uint16_t touchx, touchy;

    if (!_spitouch->bufferEmpty()) {
      bool gotChar = false;
      touch_p = _spitouch->getPoint();

      touchx = map(touch_p.y, touch_minx, touch_maxx, 0, 320);

      touchy = map(touch_p.x, touch_miny, touch_maxy, 0, 240);

      for(index = 0; index < 29; ++index) {
        if(keys[index].touched(touchx, touchy)) {
          switch (keys[index].getKeyValue()) {
            case '/':
              if(strlen(str) > 0)
                str[strlen(str)-1] = '\0';
              break;
            case ']':
              _tft->fillScreen(ILI9341_BLACK);
              retstr = String(str);
              return;
            default:
              str[strlen(str)] = keys[index].getKeyValue();
              break;
          }

          _tft->setTextColor(ILI9341_CYAN);
          _tft->setCursor(x+5, y+23);
          _tft->print(str);
          break;
        }
      }

      delay(200); // to give them a moment to let go of the key

      // clear the buffer
      do {
        _spitouch->getPoint();
      } while(!_spitouch->bufferEmpty());
    }

    yield();
  }

}

void SoftKeyboard::drawBackspace(Adafruit_ILI9341 *__tft, SoftKey k)
{
  KeyPoints kpa[9];

  float w_incr = k.getWidth() / 10;
  float h_incr = k.getHeight() / 10;

// Top left
  kpa[0].x = k.getX() + (w_incr * 4);
  kpa[0].y = k.getY() + h_incr;

// Top Right
  kpa[1].x = k.getX() + (w_incr * 10);
  kpa[1].y = k.getY() + h_incr;

// Bottom left
  kpa[2].x = k.getX() + (w_incr * 4);
  kpa[2].y = k.getY() + (h_incr * 9);

// Bottom Right
  kpa[3].x = k.getX() + (w_incr * 10);
  kpa[3].y = k.getY() + (h_incr * 9);

// Back to top left
  kpa[4].x = kpa[0].x;
  kpa[4].y = kpa[0].y;

// left point
  kpa[5].x = k.getX() + (w_incr * 2);
  kpa[5].y = k.getY() + (h_incr * 5);

// Back to bottom left
  kpa[6].x = kpa[2].x;
  kpa[6].y = kpa[2].y;

// back to bottom right
  kpa[7].x = kpa[3].x;
  kpa[7].y = kpa[3].y;

// Finally, back to top right
  kpa[8].x = kpa[1].x;
  kpa[8].y = kpa[1].y;

  drawShape(__tft, kpa, 9);
}

void SoftKeyboard::drawEnter(Adafruit_ILI9341 *__tft, SoftKey k)
{
  KeyPoints kpa[10];
  float w_incr = k.getWidth() / 10;
  float h_incr = k.getHeight() / 10;
/***********************************************************

                             point 1,10  *********** point 2
                                   7,2   *         * 9,2
                                         *         *
                 point 7                 *         *
                 *   4,2                 *         *
                **                       *         *
               * *************************         *
              *  point 8 4,5            point 9    *
    point 6  *                          7,5        *
        2,5   *  point 4 4,7                       *
               * *********************************** point 3
                **                                   9,7
                 *
                 point 5 4,9
************************************************************/
  kpa[0].x = k.getX() + (w_incr * 7);
  kpa[0].y = k.getY() + (h_incr * 2);

  kpa[1].x = k.getX() + (w_incr * 9);
  kpa[1].y = k.getY() + (h_incr * 2);

  kpa[2].x = k.getX() + (w_incr * 9);
  kpa[2].y = k.getY() + (h_incr * 7);

  kpa[3].x = k.getX() + (w_incr * 4);
  kpa[3].y = k.getY() + (h_incr * 7);

  kpa[4].x = k.getX() + (w_incr * 4);
  kpa[4].y = k.getY() + (h_incr * 9);

  kpa[5].x = k.getX() + (w_incr * 2);
  kpa[5].y = k.getY() + (h_incr * 5.5);

  kpa[6].x = k.getX() + (w_incr * 4);
  kpa[6].y = k.getY() + (h_incr * 3);

  kpa[7].x = k.getX() + (w_incr * 4);
  kpa[7].y = k.getY() + (h_incr * 5);

  kpa[8].x = k.getX() + (w_incr * 7);
  kpa[8].y = k.getY() + (h_incr * 5);

  kpa[9].x = kpa[0].x;
  kpa[9].y = kpa[0].y;

  drawShape(__tft, kpa, 10);
}

void SoftKeyboard::drawShape(Adafruit_ILI9341 *___tft, KeyPoints *k, int numPoints)
{
  for(int x = 0; x < numPoints-1; ++x) {
    ___tft->drawLine(k[x].x, k[x].y, k[x+1].x, k[x+1].y, ILI9341_BLACK);
  }
}
