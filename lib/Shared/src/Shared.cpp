#include <Shared.h>

bool gameActive;
bool lives = 3;

void setGameActive() {
  dispatchEvent(PACMAN, STATE_PACMAN_DEFAULT);
  dispatchEvent(PINKY, STATE_MONSTER_UNVULNERABLE);
  dispatchEvent(CLYDE, STATE_MONSTER_UNVULNERABLE);
  gameActive = true;
}

void setGameInactive() {
  gameActive = false;
}

bool isGameActive() {
  return gameActive;
}

void gameOver() {
  dispatchEvent(PACMAN, STATE_OFF);
  dispatchEvent(PINKY,  STATE_OFF);
  dispatchEvent(CLYDE,  STATE_OFF);
}

void pacmanDied(byte identifier) {
  if (lives == 0) {
    gameOver();
  } else {
    dispatchEvent(PACMAN, STATE_PACMAN_EATEN);
    if (identifier == PINKY) {
      dispatchEvent(PINKY, STATE_MONSTER_EATING);
    }
    if (identifier == CLYDE) {
      dispatchEvent(CLYDE, STATE_MONSTER_EATING);
    }
    lives = lives - 1;
  }
}
