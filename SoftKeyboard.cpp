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
    uint16_t touch_maxy)
{
  unsigned char letter;
  int index;
  char str[64];
/*
  uint16_t space_x, space_y, space_w, space_h;
  uint16_t backspace_x, backspace_y, backspace_w, backspace_h;
  uint16_t enter_x, enter_y, enter_w, enter_h;
*/
  memset(str, '\0', sizeof(str));

  x = xpos;
  y = ypos;
  w = width;
  h = height;
  minX = touch_minx;
  maxX = touch_maxx;
  minY = touch_miny;
  maxY = touch_maxy;

/*
  space_x = x + (w/2) - 90;
  space_y = y + 170;
  space_w = 150;
  space_h = 35;

  backspace_x = x + w - 29;
  backspace_y = y + 40 + 44;
  backspace_w = 27;
  backspace_h = 40;

  enter_x = x + w + - 59;
  enter_y = y + 40 + 44 + 40 + 3;
  enter_w = 57;
  enter_h = 40;

*/
  _tft->fillRoundRect(x, y, w, 35, 3, ILI9341_BLACK);
  _tft->drawRoundRect(x, y, w, 35, 3, ILI9341_CYAN);

  for(letter = 'a', index = 0; letter <= 'z'; ++letter, ++index)
    keys[index] = new SoftKey(_tft, x, y+40, w, h, letter);

  keys[26] = new SoftKey(_tft, x, y+40, w, h, '/');
  keys[27] = new SoftKey(_tft, x, y+40, w, h, ']');
  keys[28] = new SoftKey(_tft, x, y+40, w, h, ' ');

  for(letter = 0; letter < 29; letter++) {
    _tft->fillRoundRect(
        keys[letter]->getX(),
        keys[letter]->getY(),
        keys[letter]->getWidth(),
        keys[letter]->getHeight(),
        3,
        ILI9341_CYAN);

    _tft->drawRoundRect(
        keys[letter]->getX(),
        keys[letter]->getY(),
        keys[letter]->getWidth(),
        keys[letter]->getHeight(),
        3,
        ILI9341_DARKCYAN);

    _tft->drawChar(
        keys[letter]->getTextX(), 
        keys[letter]->getTextY(), 
        keys[letter]->getKeyValue(), 
        ILI9341_BLACK, 
        ILI9341_CYAN, 
        1);
  }

/*
  _tft->fillRoundRect(space_x, space_y, space_w, space_h, 3, ILI9341_CYAN);
  _tft->drawRoundRect(space_x, space_y, space_w, space_h, 3, ILI9341_CYAN);

  _tft->fillRoundRect(backspace_x, backspace_y, backspace_w, backspace_h, 3, ILI9341_CYAN);
  _tft->drawRoundRect(backspace_x, backspace_y, backspace_w, backspace_h, 3, ILI9341_CYAN);

  _tft->drawRect(
      backspace_x + (backspace_w/2), 
      backspace_y + (backspace_h/2) - (backspace_h/2/2), 
      (backspace_w / 2) - 5, 
      (backspace_h / 2), 
      ILI9341_BLACK);
  _tft->drawTriangle(
// top point
      backspace_x + (backspace_w/2),
      backspace_y + (backspace_h/2) - (backspace_h/2/2),
// bottom point
      backspace_x + (backspace_w / 2),
      backspace_y + (backspace_h/2) + (backspace_h/2/2) - 1,
// left point
      backspace_x + (backspace_w / 2) - 9,
      backspace_y + (backspace_h / 2),
      ILI9341_BLACK);

  _tft->fillRoundRect(enter_x, enter_y, enter_w, enter_h, 3, ILI9341_CYAN);
  _tft->drawRoundRect(enter_x, enter_y, enter_w, enter_h, 3, ILI9341_CYAN);

  _tft->fillRect(enter_x + (enter_w*.35), enter_y + (enter_h/2), enter_w/3, enter_h/4, ILI9341_BLACK);

*/
/*
  _tft->drawLine(
      backspace_x + (backspace_w/2), 
      backspace_y + (backspace_h/2) - (backspace_h/2/2),
      backspace_x + (backspace_w/2) + 5,
      backspace_y + (backspace_h/2) + (backspace_h/2/2),
      ILI9341_BLACK);

  _tft->drawLine(
      backspace_x + (backspace_w/2), 
      backspace_y + (backspace_h/2) + (backspace_h/2/2),
      backspace_x + (backspace_h/2) - (backspace_h/2/2),
      backspace_y + (backspace_h/2) - (backspace_h/2/2),
      ILI9341_BLACK);
*/

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
        if(keys[index]->touched(touchx, touchy)) {
          str[strlen(str)] = keys[index]->getKeyValue();
          _tft->setTextColor(ILI9341_CYAN);
          _tft->setCursor(x+5, y+23);
          _tft->print(str);
          gotChar = true;
          break;
        }
      }

/*
      if( ! gotChar) {
        if(touchx >= space_x && touchx <= space_x + space_w && touchy >= space_y && touchy <= space_y + space_h) {
          str[strlen(str)] = ' ';
          _tft->setTextColor(ILI9341_CYAN);
          _tft->setCursor(x+5, y+23);
          _tft->print(str);
        } else if(
            touchx >= backspace_x && 
            touchx <= backspace_x + backspace_w && 
            touchy >= backspace_y && 
            touchy <= backspace_y + backspace_h) {
          str[strlen(str)-1] = '\0';
          _tft->fillRoundRect(x, y, w, 35, 3, ILI9341_BLACK);
          _tft->drawRoundRect(x, y, w, 35, 3, ILI9341_CYAN);
          _tft->setTextColor(ILI9341_CYAN);
          _tft->setCursor(x+5, y+23);
          _tft->print(str);
        }
      }
*/
      delay(200); // to give them a moment to let go of the key

      // clear the buffer
      do {
        _spitouch->getPoint();
      } while(!_spitouch->bufferEmpty());
    }

    yield();
  }

Serial.println("done");
}

