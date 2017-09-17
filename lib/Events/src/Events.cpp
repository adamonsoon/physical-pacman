#include <Events.h>
#include <Shared.h>

byte payload[PAYLOAD_SIZE];

void setupMirf() {
  Mirf.cePin  = 7;
  Mirf.csnPin = 8;
  Mirf.spi    = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"mastr");
  Mirf.payload = PAYLOAD_SIZE;
  Mirf.config();
}

void rfDispatch(byte recipientId, byte state) {
  payload[0] = recipientId;
  payload[1] = state;
  Mirf.setTADDR((byte *)"movabaa");
  Mirf.send((byte *)payload);
  while (Mirf.isSending()) {
  }
}

void dispatchEvent(byte event, byte identifier) {

  byte id;

  switch (identifier) {
    case PACMAN:
      id = PACMAN_ID;
      break;
    case PINKY:
      id = MONSTER1_ID;
      break;
    case CLYDE:
      id = MONSTER2_ID;
      break;
  };

  switch (event) {
    case STATE_IDLE:
    case STATE_OFF:
      rfDispatch(id, STATE_IDLE);
      break;
    case STATE_PACMAN_DEFAULT:
      rfDispatch(id, STATE_PACMAN_DEFAULT);
      break;
    case STATE_PACMAN_EATING:
      rfDispatch(id, STATE_PACMAN_EATING);
      break;
    case STATE_PACMAN_EATEN:
      rfDispatch(id, STATE_PACMAN_EATEN);
      break;
    case STATE_MONSTER_VULNERABLE:
      rfDispatch(id, STATE_MONSTER_VULNERABLE);
      break;
    case STATE_MONSTER_UNVULNERABLE:
      rfDispatch(id, STATE_MONSTER_UNVULNERABLE);
      break;
    case STATE_MONSTER_INVISIBLE:
      rfDispatch(id, STATE_MONSTER_INVISIBLE);
      break;
    case STATE_MONSTER_EATING:
      rfDispatch(id, STATE_MONSTER_EATING);
      break;
  }
  Serial.println("Event fired: " + String(event));
}
