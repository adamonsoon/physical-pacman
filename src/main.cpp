#include <Scheduler.h>
#include <Physics.h>
#include <Board.h>
#include <Joystick.h>

bool shouldOutputBoard = false;

void movePlayer(int dir) {

  if (!canMove(millis(), getPreviousMove())) {
    return;
  }

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

#ifndef UNIT_TEST

void setup() {

  Serial.begin(9600);

  initPins();
  setPlayerPosition(6,0);

  if (shouldOutputBoard) {
    outputBoard();
  }
}

void loop() {

  runSchedule();

  int dir = getDirection(directions);

  if (dir != directions.none) {
    movePlayer(dir);
    return;
  }

}

#endif
