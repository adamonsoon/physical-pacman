#include <Scheduler.h>

unsigned long previousMillis = 0;

bool canMove() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= GAME_SPEED) {
    previousMillis = currentMillis;
    return true;
  }
}
