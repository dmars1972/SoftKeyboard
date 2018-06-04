#ifndef _KEYMAP
#define _KEYMAP

#define ROW_1 (1<<4)
#define ROW_2 (2<<4)
#define ROW_3 (3<<4)
#define ROW_4 (4<<4)

#define COL_1 1
#define COL_2 2
#define COL_3 3
#define COL_4 4
#define COL_5 5
#define COL_6 6
#define COL_7 7
#define COL_8 8
#define COL_9 9
#define COL_10 10

enum class KeyMap {
  q = ROW_1 | COL_1,
  w = ROW_1 | COL_2,
  e = ROW_1 | COL_3,
  r = ROW_1 | COL_4,
  t = ROW_1 | COL_5,
  y = ROW_1 | COL_6,
  u = ROW_1 | COL_7,
  i = ROW_1 | COL_8,
  o = ROW_1 | COL_9,
  p = ROW_1 | COL_10,

  a = ROW_2 | COL_1,
  s = ROW_2 | COL_2,
  d = ROW_2 | COL_3,
  f = ROW_2 | COL_4,
  g = ROW_2 | COL_5,
  h = ROW_2 | COL_6,
  j = ROW_2 | COL_7,
  k = ROW_2 | COL_8,
  l = ROW_2 | COL_9,

  z = ROW_3 | COL_2,
  x = ROW_3 | COL_3,
  c = ROW_3 | COL_4,
  v = ROW_3 | COL_5,
  b = ROW_3 | COL_6,
  n = ROW_3 | COL_7,
  m = ROW_3 | COL_8,

  bspc = ROW_2 | COL_10,
  entr = ROW_3 | COL_9,
  spc = ROW_4 | COL_3
};

#endif
