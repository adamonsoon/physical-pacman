#ifndef BOARD_H
#define BOARD_H

#include <Shared.h>

#define WALL   1
#define EMPTY  0
#define PLAYER 2
#define ENEMY  3

struct GameBoard {
  int gameStatus = GAME_INACTIVE;
  int player = PLAYER;
  int enemy  = ENEMY;
  int wall   = WALL;
  int empty  = EMPTY;
  int layout[boardMetadata.columns][boardMetadata.rows] = {
    { EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, WALL,  WALL,  EMPTY },
    { EMPTY, WALL,  WALL,  EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, WALL,  WALL,  EMPTY },
    { EMPTY, WALL,  WALL,  EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY }
  };
};

GameBoard getBoard();

int getPosValue(int c, int r);

void setPosValue(int c, int r, int val);

bool isPlayer(int c, int r);

bool isEnemy(int c, int r);

void setPlayerPosition(int c, int r, bool pulse = true);

void setEnemyPosition(int c, int r, bool pulse = true);

bool isOutOfBounds(int c, int r);

bool isNextOutOfBounds(int c, int r, int dir);

void setNextPosition(int c, int r, int dir);

void blockEntity(int c, int r);

void mapBoardToOutput(int dir);

void outputBoard();

#endif
