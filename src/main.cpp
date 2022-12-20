#include <Arduino.h>

extern "C" {
  #include "popi.h"
}

#define MOVE_SIZE 2

static char move[MOVE_SIZE];
static unsigned char move_x;
static unsigned char move_y;

static void render() {
  Serial.println("====================================");
  for(int y = 0; y < CELLS_HEIGHT; y++) {
    for(int x = 0; x < CELLS_WIDTH; x++) {
      struct CellColor *color = popi_getCellColor(x, y);
      Serial.print(popi_getCellChar(x, y));
    }
    Serial.println();
  }
}

void setup() {
  popi_newGame();

  Serial.begin(115200); // Any baud rate should work

  render();
}

static int setMove() {
  if((move[0] < 48) || (move[0]) > 57) return 0;
  if((move[1] < 48) || (move[1]) > 57) return 0;
  move_x = move[0] - '0';
  move_y = move[1] - '0';
  return 1;
}

static int getMove() {
  if (Serial.available() == 0) return 0;

  int rlen = Serial.readBytesUntil(10, move, MOVE_SIZE);
  
  while(Serial.available() > 0)
    Serial.read();

  if(rlen != 2) return 0;

  setMove();

  return 1;
}

void loop() {
  
  if(!getMove()) return;

  popi_selectCell(move_x, move_y);

  if(popi_hasUpdated()) {
    render();
  }

  if(popi_gameOver()) {
    popi_newGame();
  }
}