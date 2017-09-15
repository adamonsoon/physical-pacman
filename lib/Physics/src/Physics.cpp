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
  }

  for (int c = 0; c < boardMetadata.columns; c++) {
    for (int r = 0; r < boardMetadata.rows; r++) {
      physics.stateMap[c][r] = (PinData) {
        .x = c,
        .y = r,
        .pin = physics.pinMap[c][r],
        .state = 0
      };
    }
  }
}

void setState(PinData pin, int state) {
  physics.stateMap[pin.x][pin.y].state = state;
}

void setPinMode(int pin, int mode) {
  digitalWrite(pin, mode);
}

void setPinMode(PinData pin, int mode) {
  setState(pin, mode);
}

void sendPulse(int pin, int delay, void (*setPinMode)(int, int)) {
  unsigned long current = millis();
  schedule(pin, setPinMode, ON, current + delay);
  schedule(pin, setPinMode, OFF, current + physics.timeToReject);
}

void sendPulse(PinData pin, int delay, void (*setPinMode)(int, int)) {
  unsigned long current = millis();
  schedule(pin, setPinMode, ON, current + delay);
  schedule(pin, setPinMode, OFF, current + physics.timeToReject);
}

PinData getPinData(int c, int r) {
  return physics.stateMap[c][r];
}

PinData getPin(int c, int r) {
  return physics.stateMap[c][r];
}

void mapStateToOutput() {
  for (int c = 0; c < boardMetadata.columns; c++) {
    for (int r = 0; r < boardMetadata.rows; r++) {
      if (physics.stateMap[c][r].pin == 0) continue;
      if (physics.stateMap[c][r].pin > 100) {

      } else {

      }
    }
  }
}
