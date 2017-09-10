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

extern GameBoard getBoard();

extern int getPosValue(int c, int r);

extern void setPosValue(int c, int r, int val);

extern bool isPlayer(int c, int r);

extern bool isEnemy(int c, int r);

extern void setPlayerPosition(int c, int r, bool pulse = true);

extern void setEnemyPosition(int c, int r, bool pulse = true);

extern bool isOutOfBounds(int c, int r);

extern bool isNextOutOfBounds(int c, int r, int dir);

extern void setNextPosition(int c, int r, int dir);

extern void blockEntity(int c, int r);

extern void mapBoardToOutput(int dir);

extern void outputBoard();

#endif
