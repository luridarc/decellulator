#include <Arduino.h>

// #include <popi.h>
#include "popi.h"

static void render() {
  for(int i = 0; i < popi_getCellCount(); i++) {
    // set red with popi_getRed(i);
    // set green with popi_getGreen(i);
    // set blue with popi_getBlue(i);
  }
}

void setup() {
  popi_newGame();
}

void loop() {
  if(popi_gameOver()) {
    popi_newGame();
  }

  // get touched value x and y
  int x = 0;
  int y = 0;

  popi_selectCell(x, y);

  if(popi_hasUpdated()) {
    render();
  }
}