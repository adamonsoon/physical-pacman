/**
   A Mirf example to test the latency between two Ardunio.

   Pins:
   Hardware SPI:
   MISO -> 12
   MOSI -> 11
   SCK -> 13

   Configurable:
   CE -> 7
   CSN -> 8

   Note: To see best case latency comment out all Serial.println
   statements not displaying the result and load
   'ping_server_interupt' on the server.
*/

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define PACMAN_ID 10
#define MOSTER1_ID 20
#define MONSTER2_ID 30

#define PAYLOAD_SIZE 2
byte payload[PAYLOAD_SIZE];

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(20);
  Mirf.cePin = 7;
  Mirf.csnPin = 8;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"mastr");
  Mirf.payload = PAYLOAD_SIZE;
  //Mirf.channel = 10;
  Mirf.config();
  Serial.println("Beginning ... ");
}

void loop() {
  if (Serial.available()) {
    int recipientId = Serial.parseInt();
    int state = Serial.parseInt();
    rf_dispatch(recipientId, state);
    while (Serial.available()) {
      Serial.read();
      delay(5);
    }
  }
}

void rf_dispatch(int recipientId, int state) {
  Serial.print("sending command: "); Serial.print(payload[1]); Serial.print(" to: "); Serial.println(payload[0]);
  payload[0] = recipientId;
  payload[1] = state;
  Mirf.setTADDR((byte *)"movab");
  Mirf.send((byte *)payload);
  while (Mirf.isSending()) {
  }
}
