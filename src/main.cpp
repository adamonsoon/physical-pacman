#include <Scheduler.h>
#include <Physics.h>
#include <Board.h>
#include <Joystick.h>

bool shouldOutputBoard = true;

void movePlayer(int dir) {

  if (!canMove()) return;

  for (int c = 0; c < boardMetadata.columns; c++) {
    for (int r = 0; r < boardMetadata.rows; r++) {
      if (isPlayer(c, r)) {
        setNextPosition(c, r, dir);
        if (shouldOutputBoard) {
          outputBoard();
        }
        return;
      }
    }
  }
}

#ifndef UNIT_TEST  // IMPORTANT LINE!

void setup() {

  Serial.begin(9600);

  initPins();
  setPlayerPosition(6,0);

  if (shouldOutputBoard) {
    outputBoard();
  }
}

void loop() {

  int dir = getDirection(directions);

  if (dir != directions.none) {
    movePlayer(dir);
    return;
  }

}

#endif    // IMPORTANT LINE!
