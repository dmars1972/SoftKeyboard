Built this software keyboard for an Adafruit ESP8266 feather with
the 2.4 inch featherwing TFT.

Currently working, although I still need to add some functionality.

SoftKeyboard(
     Adafruit_ILI9341 *,   // reference to your tft object
     Adafruit_STMPE610 *,  // reference to your touchscreen
     x,                    // x position of keyboard (use 10 or so)
     y,                    // y position of keyboard (no more than 30)
     width,                // width of your screen (designed for 320, YMMV)
     height,               // height of your screen (designed for 240)
     uint16_t              // Max X of the touchscreen
     uint16_t,             // Min X of the touchscreen
     uint16_t,             // Max Y of the touchscreen
     uint16_t,             // Min Y of the touchscreen
     String&);             // string to be returned

I've got this set up for rotation 3 - if you use rotation 1, you'll just have
to rearrange the last 4 ints.

The min/max x/y coordinates are critical - they don't appear to be exactly the
same on every screen.  I'd suggest just writing a quick sketch that just 
displays the x/y coordinates when you touch the screen and figure out what your
values are by touching the corners.
