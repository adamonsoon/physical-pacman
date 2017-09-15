#include <Shared.h>
#include <Physics.h>
#include <Board.h>

GameBoard board;

GameBoard getBoard() {
  return board;
}

int getPosValue(BoardSquare s) {
  return board.layout[s.x][s.y];
}

void setPosValue(BoardSquare s, int val) {
  board.layout[s.x][s.y] = val;
}

bool isPlayer(BoardSquare s) {
  return getPosValue(s) == board.player;
}

bool isEnemy(BoardSquare s) {
  return getPosValue(s) == board.enemy;
}

void setPlayerPosition(BoardSquare s, int dir, bool pulse) {
  setPosValue(s, board.player);
  if (pulse) {
    blockEntity(s, dir, 0, board.tail);
  }
}

void setEnemyPosition(BoardSquare s, int dir, bool pulse, int identifier) {
  setPosValue(s, identifier);
  if (pulse) {
    blockEntity(s, dir, 0, board.tail);
  }
}

bool isOutOfBounds(BoardSquare s) {
  return getPosValue(s) == board.wall ||
    (s.x < 0) ||
    (s.x >= boardMetadata.columns ) ||
    (s.y < 0) ||
    (s.y >= boardMetadata.rows);
}

bool isNextOutOfBounds(BoardSquare s, int dir) {

  BoardSquare squareOob = s;

  switch (dir) {
    case directions.up:
      squareOob.x = s.x - 1;
      return isOutOfBounds(squareOob);
    case directions.down:
      squareOob.x = s.x + 1;
      return isOutOfBounds(squareOob);
    case directions.right:
      squareOob.y = s.y + 1;
      return isOutOfBounds(squareOob);
    case directions.left:
      squareOob.y = s.y - 1;
      return isOutOfBounds(squareOob);
  }

  return false;
}

BoardSquare getNextPosition(BoardSquare s, int dir) {

  BoardSquare nextPosition = s;

  switch (dir) {
    case directions.up:
      nextPosition.x = s.x - 1;
      break;
    case directions.down:
      nextPosition.x = s.x + 1;
      break;
    case directions.right:
      nextPosition.y = s.y + 1;
      break;
    case directions.left:
      nextPosition.y = s.y - 1;
      break;
  }

  return nextPosition;
}

BoardSquare setNextEnemyPosition(BoardSquare s, int dir, int identifier) {
  setPosValue(s, board.empty);
  BoardSquare nextPosition = getNextPosition(s, dir);
  setEnemyPosition(nextPosition, dir, true, identifier);
  return nextPosition;
}

BoardSquare setNextPosition(BoardSquare s, int dir) {

  if (isNextOutOfBounds(s, dir)) {
    return s;
  }

  setPosValue(s, board.empty);
  BoardSquare nextPosition = getNextPosition(s, dir);
  setPlayerPosition(nextPosition, dir);

  return nextPosition;
}

bool isBlocked(BoardSquare s) {
  return (isOutOfBounds(s) || isEnemy(s) || isPlayer(s));
}

bool shouldBlock(BoardSquare s) {
  return !(isOutOfBounds(s) || isEnemy(s) || isPlayer(s));
}

void block(BoardSquare s) {
  if (shouldBlock(s)) {
    sendPulse(getPin(s.x, s.y), 0);
  }
}

int getOppositDir(int dir) {
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

bool isSideOpen(BoardSquare s, int dir) {
  int directionsArr[4] = { directions.up, directions.right, directions.down, directions.left };
  int opDirection = getOppositDir(dir);
  BoardSquare nextPositions[4];
  bool sideOpen = false;

  for (int i = 0; i < 4; i++) {
    if (directionsArr[i] == dir) continue;
    if (directionsArr[i] == opDirection) continue;
    nextPositions[i] = getNextPosition(s, directionsArr[i]);
    if (!isBlocked(nextPositions[i])) {
      sideOpen = true;
    }
  }

  return sideOpen;
}

void blockEntity(BoardSquare s, int dir, int delay, int tail) {

  if (tail == 0) return;

  int directionsArr[4] = { directions.up, directions.right, directions.down, directions.left };
  BoardSquare nextPositions[4];
  BoardSquare nextPosition;

  int opDirection = getOppositDir(dir);
  bool isOpDirectionBlocked = isBlocked(getNextPosition(s, opDirection));
  bool sideOpen = false;

  for (int i = 0; i < 4; i++) {
    if (directionsArr[i] == dir) continue;
    nextPositions[i] = getNextPosition(s, directionsArr[i]);
    if (!(isBlocked(nextPositions[i]) || directionsArr[i] == opDirection)) {
      sideOpen = true;
    }
  }

  for (int i = 0; i < 4; i++) {
    if (directionsArr[i] == dir) continue;
    nextPosition = nextPositions[i];
    if (!isBlocked(nextPositions[i])) {
      if (directionsArr[i] == opDirection || isOpDirectionBlocked) {
        if (sideOpen && tail == board.tail) tail = 1;
        sendPulse(getPin(nextPosition.x, nextPosition.y), delay);
        blockEntity(nextPosition, dir, delay, tail - 1);
      } else {
        sendPulse(getPin(nextPosition.x, nextPosition.y), delay + 100);
        blockEntity(nextPosition, getOppositDir(directionsArr[i]), delay + 125, tail - 1);
      }
    }
  }
}

void outputBoard() {
  #ifdef DEBUG

    String row = "";

    for (int c = 0; c < boardMetadata.columns; c++) {
      for (int r = 0; r < boardMetadata.rows; r++) {
        row += board.layout[c][r];
        if (r != boardMetadata.rows - 1) {
          row += ",";
        }
      }
      Serial.println(row);
      row = "";
    }

    Serial.println("--------");

  #endif
}
