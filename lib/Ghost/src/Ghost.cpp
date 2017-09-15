#include <Ghost.h>
#include <Player.h>

#define PREFER_X 0
#define PREFER_Y 1

Ghost randomGhost = (Ghost) {
  .pos = (BoardSquare) {
    .x = 0,
    .y = 0
  },
  .state = 0,
  .prevDir = directions.none,
  .currentDir = directions.none,
  .identifier = 5,
  .previousMove = 0
};

Ghost& getRandomGhost() {
  return randomGhost;
}

void setGhostPosition(BoardSquare s, int dir, bool pulse, int identifier) {
  if (identifier == 5) {
    setEnemyPosition(randomGhost.pos, dir, pulse, identifier);
  }
}

void setRandomGhostPosition(BoardSquare s, int dir, bool pulse, int identifier) {
  randomGhost.pos.x = s.x;
  randomGhost.pos.y = s.y;
  setEnemyPosition(randomGhost.pos, dir, pulse, randomGhost.identifier);
}

int getRandomGhostMove() {

  int newDir;
  int count = 0;

  int xDis = randomGhost.pos.x - getPlayer().pos.x;
  int yDis = randomGhost.pos.y - getPlayer().pos.y;

  bool preferredDir = abs(xDis) > abs(yDis);

  if (xDis == 0) {
    preferredDir = PREFER_Y;
  }

  if (yDis == 0) {
    preferredDir = PREFER_X;
  }

  if (isNextOutOfBounds(randomGhost.pos, randomGhost.currentDir) || randomGhost.currentDir == directions.none || isSideOpen(randomGhost.pos, randomGhost.currentDir)) {

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

    bool newDirIsOppositeToCurrent = newDir == getOppositDir(randomGhost.currentDir);
    bool newDirIsBlocked = isNextOutOfBounds(randomGhost.pos, newDir);

    while (newDirIsOppositeToCurrent || newDirIsBlocked) {
      count++;
      newDir = random(1,5);
      newDirIsOppositeToCurrent = newDir == getOppositDir(randomGhost.currentDir);
      newDirIsBlocked = isNextOutOfBounds(randomGhost.pos, newDir);
      if (count > 25) {
        return getOppositDir(randomGhost.currentDir);
      }
    }

    randomGhost.prevDir = randomGhost.currentDir;
    randomGhost.currentDir = newDir;
  } else {
    newDir = randomGhost.currentDir;
  }

  BoardSquare nextPosition = getNextPosition(s, dir);

  if (isSamePosition(nextPosition, getPlayer().pos)) {

  }

  return newDir;
}

void moveRandomGhost() {
  unsigned long current = millis();
  bool movable = canMoveGhost(current, randomGhost.previousMove);
  if (!movable) return;
  randomGhost.previousMove = current;

  BoardSquare nextPosition = setNextEnemyPosition(randomGhost.pos, getRandomGhostMove(), randomGhost.identifier);
  randomGhost.pos.x = nextPosition.x;
  randomGhost.pos.y = nextPosition.y;
  delay(1000);

  #if DEBUG
    #if OUTPUT_BOARD
      outputBoard();
    #endif
  #endif
}

Ghost geteGhost(int identifier) {
    if (identifier == 5) {
      return getRandomGhost();
    }
}

void moveGhost(int identifier) {
    if (identifier == 5) {
      moveRandomGhost();
    }
}
