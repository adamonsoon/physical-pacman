#include <Shared.h>
#include <Physics.h>
#include <Board.h>
#include <Events.h>
#include <MemoryFree.h>

GameBoard board;

GameBoard& getBoard() {
  return board;
}

byte enemyState = STATE_ENEMIES_NORMAL;

void getEnemyState(byte state) {
  enemyState = state;
}

void setEnemyState(byte state, bool shouldDispatch) {
  Serial.println("new ghost state: " + String(state));
  enemyState = state;

  if (shouldDispatch) {
    switch(state) {
      case STATE_MONSTER_UNVULNERABLE:
        dispatchEvent(PINKY, STATE_MONSTER_UNVULNERABLE);
        dispatchEvent(CLYDE, STATE_MONSTER_UNVULNERABLE);
        break;
      case STATE_MONSTER_VULNERABLE:
        dispatchEvent(PINKY, STATE_MONSTER_VULNERABLE);
        dispatchEvent(CLYDE, STATE_MONSTER_VULNERABLE);
        break;
      case STATE_MONSTER_WEAK:
        dispatchEvent(PINKY, STATE_MONSTER_WEAK);
        dispatchEvent(CLYDE, STATE_MONSTER_WEAK);
        break;
    }
  }
}

byte getPosValue(BoardSquare* s) {
  return board.layout[s->x][s->y];
}

void setPosValue(BoardSquare* s, byte val) {
  board.layout[s->x][s->y] = val;
}

bool isPlayer(BoardSquare* s) {
  return getPosValue(s) == PACMAN;
}

bool isEnemy(BoardSquare* s) {
  return getPosValue(s) == PINKY || getPosValue(s) == CLYDE;
}

void setPlayerPosition(BoardSquare* s, byte dir, bool pulse) {
  setPosValue(s, PACMAN);
  if (pulse) {
    blockEntity(s, dir, 0, TAIL_LENGTH);
  }
}

void setEnemyPosition(BoardSquare* s, byte dir, bool pulse, byte identifier) {
  setPosValue(s, identifier);
  if (pulse) {
    blockEntity(s, dir, 0, TAIL_LENGTH);
  }
}

bool isOutOfBounds(BoardSquare* s) {
  return getPosValue(s) == WALL ||
    (s->x < 0) ||
    (s->x >= boardMetadata.columns ) ||
    (s->y < 0) ||
    (s->y >= boardMetadata.rows);
}

bool isNextOutOfBounds(BoardSquare* s, byte dir) {

  BoardSquare squareOob;
    squareOob.x = s->x;
    squareOob.y = s->y;

  switch (dir) {
    case directions.up:
      squareOob.x = s->x - 1;
      return isOutOfBounds(&squareOob);
    case directions.down:
      squareOob.x = s->x + 1;
      return isOutOfBounds(&squareOob);
    case directions.right:
      squareOob.y = s->y + 1;
      return isOutOfBounds(&squareOob);
    case directions.left:
      squareOob.y = s->y - 1;
      return isOutOfBounds(&squareOob);
  }

  return false;
}

BoardSquare getNextPosition(BoardSquare* s, byte dir) {

  BoardSquare nextPosition;

  nextPosition.x = s->x;
  nextPosition.y = s->y;

  switch (dir) {
    case directions.up:
      nextPosition.x = s->x - 1;
      break;
    case directions.down:
      nextPosition.x = s->x + 1;
      break;
    case directions.right:
      nextPosition.y = s->y + 1;
      break;
    case directions.left:
      nextPosition.y = s->y - 1;
      break;
  }

  return nextPosition;
}

BoardSquare setNextEnemyPosition(BoardSquare* s, byte dir, byte identifier) {
  setPosValue(s, EMPTY);
  BoardSquare nextPosition = getNextPosition(s, dir);
  setEnemyPosition(&nextPosition, dir, true, identifier);
  return nextPosition;
}

BoardSquare setNextPosition(BoardSquare* s, byte dir) {

  if (isNextOutOfBounds(s, dir)) {
    return *s;
  }

  setPosValue(s, EMPTY);
  BoardSquare nextPosition = getNextPosition(s, dir);
  setPlayerPosition(&nextPosition, dir);

  return nextPosition;
}

bool isBlocked(BoardSquare* s) {
  return (isOutOfBounds(s));
}

bool shouldBlock(BoardSquare* s) {
  return !(isOutOfBounds(s));
}

void block(BoardSquare* s) {
  if (shouldBlock(s)) {
    sendPulse(getPin(s->x, s->y), 0);
  }
}

byte getOppositDir(byte dir) {
  switch (dir) {
    case directions.up:
      return directions.down;
    case directions.down:
      return directions.up;
    case directions.right:
      return directions.left;
    case directions.left:
      return directions.right;
  }
  return directions.none;
}

bool isSideOpen(BoardSquare* s, byte dir) {
  byte directionsArr[4] = { directions.up, directions.right, directions.down, directions.left };
  byte opDirection = getOppositDir(dir);
  BoardSquare nextPositions[4];
  bool sideOpen = false;

  for (byte i = 0; i < 4; i++) {
    if (directionsArr[i] == dir) continue;
    if (directionsArr[i] == opDirection) continue;
    nextPositions[i] = getNextPosition(s, directionsArr[i]);
    if (!isBlocked(&nextPositions[i])) {
      sideOpen = true;
    }
  }

  return sideOpen;
}

void blockEntity(BoardSquare* s, byte dir, byte delay, byte tail) {

  if (tail == 0) return;

  byte directionsArr[4] = { directions.up, directions.right, directions.down, directions.left };
  BoardSquare nextPositions[4];
  BoardSquare nextPosition;

  byte opDirection = getOppositDir(dir);
  BoardSquare isBlockedNextPos = getNextPosition(s, opDirection);
  bool isOpDirectionBlocked = isBlocked(&isBlockedNextPos);
  bool sideOpen = false;

  for (byte i = 0; i < 4; i++) {
    if (directionsArr[i] == dir) continue;
    nextPositions[i] = getNextPosition(s, directionsArr[i]);
    if (!(isBlocked(&nextPositions[i]) || directionsArr[i] == opDirection)) {
      sideOpen = true;
    }
  }

  for (byte i = 0; i < 4; i++) {
    if (directionsArr[i] == dir) continue;
    nextPosition = nextPositions[i];
    if (!isBlocked(&nextPositions[i])) {
      if (directionsArr[i] == opDirection || isOpDirectionBlocked) {
        if (sideOpen && tail == TAIL_LENGTH) tail = 1;
        sendPulse(getPin(nextPosition.x, nextPosition.y), delay);
        blockEntity(&nextPosition, dir, delay, tail - 1);
      } else {
        sendPulse(getPin(nextPosition.x, nextPosition.y), delay + 100);
        blockEntity(&nextPosition, getOppositDir(directionsArr[i]), delay + 125, tail - 1);
      }
    }
  }
}

bool isSamePosition(BoardSquare* p1, BoardSquare* p2) {
  return (p1->x == p2->x) && (p1->y == p2->y);
}

void outputBoard() {
  #ifdef DEBUG

    String row = "";

    for (byte c = 0; c < boardMetadata.columns; c++) {
      for (byte r = 0; r < boardMetadata.rows; r++) {
        row += board.layout[c][r];
        if (r != boardMetadata.rows - 1) {
          row += ",";
        }
      }
      Serial.println(row);
      row = "";
    }

    Serial.println("--------");
    Serial.println("Free mem: " + String(freeMemory()) + " ---- ");

  #endif
}
