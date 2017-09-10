#include "Shared.h"
#include "Physics.h"
#include "Board.h"

GameBoard board;

GameBoard getBoard() {
  return board;
}

int getPosValue(int c, int r) {
  return board.layout[c][r];
}

void setPosValue(int c, int r, int val) {
  board.layout[c][r] = val;
}

bool isPlayer(int c, int r) {
  return getPosValue(c, r) == board.player;
}

bool isEnemy(int c, int r) {
  return getPosValue(c, r) == board.enemy;
}

void setPlayerPosition(int c, int r, bool pulse) {
  setPosValue(c, r, board.player);
  if (pulse) {
    blockEntity(c, r);
    sendPulse(getPin(c,r));
  }
}

void setEnemyPosition(int c, int r, bool pulse) {
  setPosValue(c, r, board.enemy);
  if (pulse) {
    blockEntity(c, r);
    sendPulse(getPin(c,r));
  }
}

bool isOutOfBounds(int c, int r) {
  return getPosValue(c, r) == board.wall ||
    (c < 0) ||
    (c >= boardMetadata.columns ) ||
    (r < 0) ||
    (r >= boardMetadata.rows);
}

bool isNextOutOfBounds(int c, int r, int dir) {
  switch (dir) {
    case directions.up:
      return isOutOfBounds(c - 1, r);
    case directions.right:
      return isOutOfBounds(c, r + 1);
    case directions.down:
      return isOutOfBounds(c + 1, r);
    case directions.left:
      return isOutOfBounds(c, r - 1);
  }
  return false;
}

void setNextPosition(int c, int r, int dir) {

  if (isNextOutOfBounds(c, r, dir)) {
    return;
  }

  setPosValue(c, r, board.empty);

  switch (dir) {
    case directions.up:
      setPlayerPosition(c - 1, r);
      break;
    case directions.right:
      setPlayerPosition(c, r + 1);
      break;
    case directions.down:
      setPlayerPosition(c + 1, r);
      break;
    case directions.left:
      setPlayerPosition(c, r - 1);
      break;
  }
}

void blockEntity(int c, int r) {
  getPosValue(c + 1, r);
}

void outputBoard() {
    Serial.println(String(board.layout[0][0]) + "," + board.layout[0][1] + "," + board.layout[0][2] + "," + board.layout[0][3]);
    Serial.println(String(board.layout[1][0]) + "," + board.layout[1][1] + "," + board.layout[1][2] + "," + board.layout[1][3]);
    Serial.println(String(board.layout[2][0]) + "," + board.layout[2][1] + "," + board.layout[2][2] + "," + board.layout[2][3]);
    Serial.println(String(board.layout[3][0]) + "," + board.layout[3][1] + "," + board.layout[3][2] + "," + board.layout[3][3]);
    Serial.println(String(board.layout[4][0]) + "," + board.layout[4][1] + "," + board.layout[4][2] + "," + board.layout[4][3]);
    Serial.println(String(board.layout[5][0]) + "," + board.layout[5][1] + "," + board.layout[5][2] + "," + board.layout[5][3]);
    Serial.println(String(board.layout[6][0]) + "," + board.layout[6][1] + "," + board.layout[6][2] + "," + board.layout[6][3]);
    Serial.println("--------");
}
