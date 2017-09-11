#include <Arduino.h>
#include <Shared.h>
#include <Physics.h>
#include <Scheduler.h>

Physics physics;

Physics getPhysics() {
  return physics;
}

void initPins() {
  for (int i = (physics.minPin + physics.pinOffset); i <= (physics.maxPin + physics.pinOffset); i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, physics.isOff);
  }
}

void setPinMode(int pin, int mode) {
  digitalWrite(pin, mode);
}

void sendPulse(int pin) {

  unsigned long current = millis();

  for (int i = 0; i < physics.numberOfPulses; i++) {
    schedule(pin, setPinMode, ON, current);
    schedule(pin, setPinMode, OFF, current + physics.timeToReject + 1);
    current += physics.timeToReject + physics.timeToRest + 1;
  }
}

int getPin(int c, int r) {
  return physics.pinMap[c][r] + physics.pinOffset;
}

void blockLeftRight(int c, int r) {
  if (r != 0) {
      sendPulse(getPin(c, r - 1));
  }

  if (r != boardMetadata.rows - 1) {
      sendPulse(getPin(c, r + 1));
  }
}

void blockTopBottom(int c, int r) {
  if (c != 0) {
      sendPulse(getPin(c - 1, r));
  }

  if (r != boardMetadata.columns - 1) {
      sendPulse(getPin(c + 1, r));
  }
}
