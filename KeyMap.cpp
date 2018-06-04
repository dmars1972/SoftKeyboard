#include "KeyMap.h"

KeyMap operator++(KeyMap &keyMap)
{
  switch(keyMap) {
    q:  return KeyMap::w;
        break;
    w:  return KeyMap::e;
        break;
    e:  return KeyMap::r;
        break;
    r:  return KeyMap::t;
        break;
    t:  return KeyMap::y;
        break;
    y:  return KeyMap::u;
        break;
    u:  return KeyMap::i;
        break;
    i:  return KeyMap::o;
        break;
    o:  return KeyMap::p;
        break;
    p:  return KeyMap::a;
        break;
    a:  return KeyMap::s;
        break;
    s:  return KeyMap::d;
        break;
    d:  return KeyMap::f;
        break;
    f:  return KeyMap::g;
        break;
    g:  return KeyMap::h;
        break;
    h:  return KeyMap::j;
        break;
    j:  return KeyMap::k;
        break;
    k:  return KeyMap::l;
        break;
    l:  return KeyMap::z;
        break;
    z:  return KeyMap::x;
        break;
    x:  return KeyMap::c;
        break;
    c:  return KeyMap::v;
        break;
    v:  return KeyMap::b;
        break;
    b:  return KeyMap::n;
        break;
    n:  return KeyMap::m;
        break;
    m:  return KeyMap::q;
        break;
  }
}
