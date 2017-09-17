#include <Ghost.h>
#include <Player.h>

#define PREFER_X 0
#define PREFER_Y 1

Ghost clyde = (Ghost) {
  .pos = (BoardSquare) {
    .x = 0,
    .y = 0
  },
  .state = STATE_GHOST_DEFAULT,
  .prevDir = directions.none,
  .currentDir = directions.none,
  .identifier = CLYDE,
  .previousMove = 0
};

Ghost pinky = (Ghost) {
  .pos = (BoardSquare) {
    .x = 0,
    .y = 0
  },
  .state = STATE_GHOST_DEFAULT,
  .prevDir = directions.none,
  .currentDir = directions.none,
  .identifier = PINKY,
  .previousMove = 0
};

Ghost& getPinky() {
  return pinky;
}

Ghost& getClyde() {
  return clyde;
}

void setGhostPosition(BoardSquare* s, byte dir, bool pulse, Ghost& ghost) {
  ghost.pos.x = s->x;
  ghost.pos.y = s->y;
  setEnemyPosition(&ghost.pos, dir, pulse, ghost.identifier);
}

byte getGhostMove(Ghost& ghost) {

  byte newDir;
  byte count = 0;

  byte xDis = ghost.pos.x - getPlayer().pos.x;
  byte yDis = ghost.pos.y - getPlayer().pos.y;

  bool preferredDir = abs(xDis) > abs(yDis);

  if (xDis == 0) {
    preferredDir = PREFER_Y;
  }

  if (yDis == 0) {
    preferredDir = PREFER_X;
  }

  if (isNextOutOfBounds(&ghost.pos, ghost.currentDir) || ghost.currentDir == directions.none || isSideOpen(&ghost.pos, ghost.currentDir)) {

    if (preferredDir == PREFER_X) {
      if (xDis > 0) {
        newDir = directions.left;
      } else {
        newDir = directions.right;
      }
    }

    if (preferredDir == PREFER_Y) {
      if (yDis > 0) {
        newDir = directions.up;
      } else {
        newDir = directions.down;
      }
    }

    bool newDirIsOppositeToCurrent = newDir == getOppositDir(ghost.currentDir);
    bool newDirIsBlocked = isNextOutOfBounds(&ghost.pos, newDir);

    while (newDirIsOppositeToCurrent || newDirIsBlocked) {
      count++;
      newDir = random(1,5);
      newDirIsOppositeToCurrent = newDir == getOppositDir(ghost.currentDir);
      newDirIsBlocked = isNextOutOfBounds(&ghost.pos, newDir);
      if (count > 25) {
        return getOppositDir(ghost.currentDir);
      }
    }
    ghost.prevDir = ghost.currentDir;
    ghost.currentDir = newDir;
  } else {
    newDir = ghost.currentDir;
  }

  BoardSquare nextPosition = getNextPosition(&ghost.pos, newDir);

  if (isSamePosition(&nextPosition, &getPlayer().pos)) {
    setGameInactive();
    pacmanDied(ghost.identifier);
    return directions.none;
  }

  return newDir;
}

void moveGhost(Ghost& ghost) {
  unsigned long current = millis();
  bool movable = canMoveGhost(current, ghost.previousMove);
  if (!movable) return;
  ghost.previousMove = current;

  BoardSquare nextPosition = setNextEnemyPosition(&ghost.pos, getGhostMove(ghost), ghost.identifier);
  ghost.pos.x = nextPosition.x;
  ghost.pos.y = nextPosition.y;
  delay(1000);

  #if DEBUG
    #if OUTPUT_BOARD
      outputBoard();
    #endif
  #endif
}
