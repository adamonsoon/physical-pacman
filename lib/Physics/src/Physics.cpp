#include <Arduino.h>
#include <Shared.h>
#include <Physics.h>

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

void sendPulse(int pin) {
  for (int pulse = 0; pulse < physics.numberOfPulses; pulse++) {
    digitalWrite(pin, physics.isOn);
    delay(physics.timeToReject);
    digitalWrite(pin, physics.isOff);
    delay(physics.timeToRest);
  }
  digitalWrite(pin, physics.isOff);
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
