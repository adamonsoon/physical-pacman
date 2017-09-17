#ifndef BOARD_H
#define BOARD_H

#include <Shared.h>
#include <Events.h>

struct GameBoard {
  byte layout[boardMetadata.columns][boardMetadata.rows] = {
    { EMPTY,    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY    },
    { EMPTY,    WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY    },
    { EMPTY,    WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY    },
    { POWER_UP, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, POWER_UP },
    { WALL,     WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL     },
    { WALL,     WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL     },
    { EMPTY,    EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY    },
    { EMPTY,    WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY    },
    { EMPTY,    WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY    },
    { EMPTY,    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY,  WALL,  WALL, EMPTY, WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY    },
    { EMPTY,    WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY    },
    { EMPTY,    WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY,  WALL, WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY    },
    { EMPTY,    EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY    },
    { WALL,     WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL     },
    { WALL,     WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL     },
    { POWER_UP, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, WALL,  WALL,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, POWER_UP },
    { EMPTY,    WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY    },
    { EMPTY,    WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY, WALL,  WALL,  EMPTY, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  EMPTY    },
    { EMPTY,    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY    }
  };
};

struct BoardSquare {
  byte x, y;
};

GameBoard& getBoard();

extern byte getPosValue(BoardSquare* s);

extern void setPosValue(BoardSquare* s, byte val);

extern bool isPlayer(BoardSquare* s);

extern bool isEnemy(BoardSquare* s);

extern bool isSamePosition(BoardSquare* p1, BoardSquare* p2);

extern void setPlayerPosition(BoardSquare* s, byte dir, bool pulse = true);

extern void setEnemyPosition(BoardSquare* s, byte dir, bool pulse, byte identifier);

extern bool isOutOfBounds(BoardSquare* s);

extern bool isNextOutOfBounds(BoardSquare* s, byte dir);

extern bool isSideOpen(BoardSquare* s, byte dir);

extern BoardSquare getNextPosition(BoardSquare* s, byte dir);

extern BoardSquare setNextEnemyPosition(BoardSquare* s, byte dir, byte identifier);

extern BoardSquare setNextPosition(BoardSquare* s, byte dir);

extern void blockEntity(BoardSquare* s, byte dir, byte delay, byte tail);

extern void mapBoardToOutput(byte dir);

extern void outputBoard();

extern byte getOppositDir(byte dir);

extern void setEnemyState(byte state, bool shouldDispatch);

#endif
