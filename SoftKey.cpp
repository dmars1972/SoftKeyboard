#include "SoftKey.h"

SoftKey::SoftKey(
    Adafruit_ILI9341 *tft,
    uint16_t xpos,  // x, y, w and h are absolute to the keyboard
    uint16_t ypos,
    uint16_t width, 
    uint16_t height,
    char key,
    uint8_t keyWidthMult)
{
  int16_t t_x, t_y;
  uint16_t t_w, t_h;
  char keyString[2];
  char str[128];

  keyValue = key;
  widthMult = keyWidthMult;

  switch (tolower(keyValue)) {
      case 'a':  
            keyMap = KeyMap::a;
            break;
      case 'b':  
            keyMap = KeyMap::b;
            break;
      case 'c':  
            keyMap = KeyMap::c;
            break;
      case 'd':  
            keyMap = KeyMap::d;
            break;
      case 'e':  
            keyMap = KeyMap::e;
            break;
      case 'f':  
            keyMap = KeyMap::f;
            break;
      case 'g':  
            keyMap = KeyMap::g;
            break;
      case 'h':  
            keyMap = KeyMap::h;
            break;
      case 'i':  
            keyMap = KeyMap::i;
            break;
      case 'j':  
            keyMap = KeyMap::j;
            break;
      case 'k':  
            keyMap = KeyMap::k;
            break;
      case 'l':  
            keyMap = KeyMap::l;
            break;
      case 'm':  
            keyMap = KeyMap::m;
            break;
      case 'n':  
            keyMap = KeyMap::n;
            break;
      case 'o':  
            keyMap = KeyMap::o;
            break;
      case 'p':  
            keyMap = KeyMap::p;
            break;
      case 'q':  
            keyMap = KeyMap::q;
            break;
      case 'r':  
            keyMap = KeyMap::r;
            break;
      case 's':  
            keyMap = KeyMap::s;
            break;
      case 't':  
            keyMap = KeyMap::t;
            break;
      case 'u':  
            keyMap = KeyMap::u;
            break;
      case 'v':  
            keyMap = KeyMap::v;
            break;
      case 'w':  
            keyMap = KeyMap::w;
            break;
      case 'x':  
            keyMap = KeyMap::x;
            break;
      case 'y':  
            keyMap = KeyMap::y;
            break;
      case 'z':
            keyMap = KeyMap::z;
            break;
      case '/':
            keyMap = KeyMap::bspc;
            break;
      case ']':
            keyMap = KeyMap::entr;
            break;
      case ' ':
            keyMap = KeyMap::spc;
            break;
  }

  w = (width / 10)-1;
  h = (height / 3)-1;

  x = xpos + ((getColumn(keyMap)-1) * (w+1));
  y = ypos + ((getRow(keyMap)-1) * (h+1));

  if(isupper(keyValue)) {
    isUpper = true;
  } else {
    isUpper = false;
  }

  keyValue = tolower(keyValue);
  upperValue = toupper(keyValue);

  borderColor = ILI9341_DARKCYAN;
  textColor = ILI9341_WHITE;
  flickerColor = ILI9341_WHITE;
  fillColor = ILI9341_CYAN;

  text_x = x + (w-20);
  text_y = y + (h - 16);
}

bool SoftKey::touched(uint16_t tx, uint16_t ty)
{
  if(tx >= x && tx <= x+w && ty >= y && ty <= y+h)
    return true;

  return false;
}
