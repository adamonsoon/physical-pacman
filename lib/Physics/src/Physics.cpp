#include <Arduino.h>
#include <Shared.h>
#include <Physics.h>
#include <Scheduler.h>

Physics physics;

Physics getPhysics() {
  return physics;
}

void initPins() {
  for (byte i = (physics.minPin + physics.pinOffset); i <= (physics.maxPin + physics.pinOffset); i++) {
    pinMode(i, OUTPUT);
  }

  for (byte c = 0; c < boardMetadata.columns; c++) {
    for (byte r = 0; r < boardMetadata.rows; r++) {
      physics.stateMap[c][r] = (PinData) {
        .x = c,
        .y = r,
        .pin = physics.pinMap[c][r],
        .state = 0
      };
    }
  }
}

void setState(PinData pin, byte state) {
  physics.stateMap[pin.x][pin.y].state = state;
}

void setPinMode(byte pin, byte mode) {
  digitalWrite(pin, mode);
}

void setPinMode(PinData pin, byte mode) {
  setState(pin, mode);
}

void sendPulse(byte pin, byte delay, void (*setPinMode)(byte, byte)) {
  unsigned long current = millis();
  schedule(pin, setPinMode, ON, current + delay);
  schedule(pin, setPinMode, OFF, current + physics.timeToReject);
}

void sendPulse(PinData pin, byte delay, void (*setPinMode)(byte, byte)) {
  unsigned long current = millis();
  schedule(pin, setPinMode, ON, current + delay);
  schedule(pin, setPinMode, OFF, current + physics.timeToReject);
}

PinData getPinData(byte c, byte r) {
  return physics.stateMap[c][r];
}

PinData getPin(byte c, byte r) {
  return physics.stateMap[c][r];
}

void mapStateToOutput() {
  for (byte c = 0; c < boardMetadata.columns; c++) {
    for (byte r = 0; r < boardMetadata.rows; r++) {
      if (physics.stateMap[c][r].pin == 0) continue;
      if (physics.stateMap[c][r].pin > 100) {

      } else {

      }
    }
  }
}
