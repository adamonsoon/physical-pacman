#include <Arduino.h>
#include <Scheduler.h>
#include <Physics.h>
#include <Board.h>
#include <Player.h>
#include <Ghost.h>
#include <Joystick.h>
#include <Events.h>
#include <MemoryFree.h>

Ghost randGhost = getRandomGhost();

#ifndef UNIT_TEST

void _init() {
  initPins();
  initJoy();

  BoardSquare initialPosition;
  initialPosition.x = 0;
  initialPosition.y = 0;

  BoardSquare initialRandomGhostPosition;
  initialRandomGhostPosition.x = 8;
  initialRandomGhostPosition.y = 12;

  setInitialPlayerPosition(initialPosition, directions.none);
  setRandomGhostPosition(initialRandomGhostPosition, directions.none, true, randGhost.identifier);

  // moveAllToPlace();

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

  if (!gameActive) {
    return;
  }

  moveGhost(randGhost.identifier);

  int dir = getDirection(directions);

  if (dir != directions.none) {
    movePlayer(dir);
    return;
  }
}

#endif
