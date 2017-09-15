#ifndef BOARD_H
#define BOARD_H

#include <Shared.h>
#include <Events.h>

#define TAIL_LENGTH 2
#define WALL   1
#define EMPTY  0
#define PLAYER 2
#define ENEMY  3

struct GameBoard {
  int gameStatus = GAME_INACTIVE;
  int tail   = TAIL_LENGTH;
  int player = PLAYER;
  int enemy  = ENEMY;
  int wall   = WALL;
  int empty  = EMPTY;
  byte layout[boardMetadata.columns][boardMetadata.rows] = {
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY },
    { EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL  },
    { WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL  },
    { EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY },
    { EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY },
    { EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY },
    { WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL  },
    { WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL  },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY },
    { EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
  };
};

struct BoardSquare {
  int x, y;
};

GameBoard getBoard();

extern int getPosValue(BoardSquare s);

extern void setPosValue(BoardSquare s, int val);

extern bool isPlayer(BoardSquare s);

extern bool isEnemy(BoardSquare s);

extern void setPlayerPosition(BoardSquare s, int dir, bool pulse = true);

extern void setEnemyPosition(BoardSquare s, int dir, bool pulse, int identifier);

extern bool isOutOfBounds(BoardSquare s);

extern bool isNextOutOfBounds(BoardSquare s, int dir);

extern bool isSideOpen(BoardSquare s, int dir);

extern BoardSquare setNextEnemyPosition(BoardSquare s, int dir, int identifier);

extern BoardSquare setNextPosition(BoardSquare s, int dir);

extern void blockEntity(BoardSquare s, int dir, int delay, int tail);

extern void mapBoardToOutput(int dir);

extern void outputBoard();

extern int getOppositDir(int dir);

#endif
