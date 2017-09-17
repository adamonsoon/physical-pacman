#include <Arduino.h>
#include <Scheduler.h>
#include <Physics.h>
#include <Board.h>
#include <Player.h>
#include <Ghost.h>
#include <Joystick.h>
#include <Events.h>
#include <MemoryFree.h>

#ifndef UNIT_TEST

void _init() {

  setupMirf();
  initPins();
  initJoy();

  BoardSquare initialPosition;
  initialPosition.x = 0;
  initialPosition.y = 0;

  BoardSquare initialPinkyPosition;
  initialPinkyPosition.x = 8;
  initialPinkyPosition.y = 12;

  BoardSquare initialClydePosition;
  initialClydePosition.x = 8;
  initialClydePosition.y = 15;

  setInitialPlayerPosition(&initialPosition, directions.none);
  setGhostPosition(&initialPinkyPosition, directions.none, true, getPinky());
  setGhostPosition(&initialClydePosition, directions.none, true, getClyde());

  setGameActive();

  #if DEBUG
    #if OUTPUT_BOARD
      outputBoard();
    #endif
  #endif
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(6));
  _init();
}

void loop() {

  runSchedule();

  if (!isGameActive()) {
    return;
  }

  moveGhost(getPinky());
  moveGhost(getClyde());

  byte dir = getDirection(directions);

  if (dir != directions.none) {
    movePlayer(dir);
    return;
  }
}

#endif
