#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define PACMAN_ID 10
#define MOSTER1_ID 20
#define MONSTER2_ID 30

#define MY_ID PACMAN_ID

#define PAYLOAD_SIZE 2
byte payload[PAYLOAD_SIZE];

#define STATE_IDLE 1
#define STATE_OFF 2
#define STATE_PACMAN_DEFAULT 3
#define STATE_MONSTER_VULNERABLE 4
#define STATE_MONSTER_UNVULNERABLE 8
#define STATE_PACMAN_EATING 5
#define STATE_FEASTING 6
#define STATE_PACMAN_EATEN 7

// yellow
//#define DEFAULT_R 255
//#define DEFAULT_G 128
//#define DEFAULT_B 0

// pink
#define DEFAULT_R 100
#define DEFAULT_G 20
#define DEFAULT_B 100

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      20

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 0; // delay for half a second

int state = STATE_PACMAN_DEFAULT;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(20);
  mirfSetup();
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  Serial.println(state);
  mirfUpdate();
  switch (state) {
    case STATE_IDLE:
      state = handleIdle();
      break;
    case STATE_OFF:
      state = handleOff();
      break;
    case STATE_PACMAN_DEFAULT:
      state = handleDefault();
      break;
    case STATE_MONSTER_VULNERABLE:
      state = handleVulnerable();
      break;
    case STATE_MONSTER_UNVULNERABLE:
      state = handleUnvulnerable();
      break;
    case STATE_PACMAN_EATING:
      state = handleEating();
      break;
    case STATE_FEASTING:
      state = handleFeasting();
      break;
    case STATE_PACMAN_EATEN:
      state = handleEaten();
      break;
  }
}

int handleOff() {
  pixels.setPixelColor(18, pixels.Color(0, 0, 0)); // Left Eye
  pixels.setPixelColor(19, pixels.Color(0, 0, 0)); // Right Eye
  //Body lights
  for (int i = 0; i < NUMPIXELS - 2; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  return STATE_IDLE;
}

int vYellowVal = 0;
int vYellowDir = 1;

int handleDefault() {
  pixels.setPixelColor(18, pixels.Color(50, 50, 50)); // Left Eye
  pixels.setPixelColor(19, pixels.Color(50, 50, 50)); // Right Eye
  for (int i = 0; i < NUMPIXELS - 2; i++) {
    pixels.setPixelColor(i, pixels.Color(vYellowVal, vYellowVal, 0)); 
  }
  vYellowVal+= vYellowDir;
  if(vYellowVal == 0 || vYellowVal == 255) {
    vYellowDir *= -1;
  }
  pixels.show();
  if (Serial.available()) {
    int rv = Serial.parseInt();
    while(Serial.available()) {
      Serial.read();
      delay(10);
    }
    return rv;
  }
  else {
    delay(5);
    return STATE_PACMAN_DEFAULT;
  }
}

int handleIdle() {
  allOff();  
  if (Serial.available()) {
    int rv = Serial.parseInt();
    while(Serial.available()) {
      Serial.read();
      delay(10);
    }
    return rv;
  }
  else {
    return STATE_IDLE;
  }
}

int vBlueVal = 0;
int vBlueDir = 1;
int vBlueCount = 0;

int handleVulnerable() {
  pixels.setPixelColor(18, pixels.Color(50, 50, 50)); // Left Eye
  pixels.setPixelColor(19, pixels.Color(50, 50, 50)); // Right Eye
  for (int i = 0; i < NUMPIXELS - 2; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, vBlueVal)); 
  }
  vBlueVal+= vBlueDir;
  if(vBlueVal == 0 || vBlueVal == 255) {
    vBlueDir *= -1;
  }
  pixels.show();
  //delayMicroseconds(250);
  vBlueCount++;
  return STATE_MONSTER_VULNERABLE;
}

int handleUnvulnerable() {
  pixels.setPixelColor(18, pixels.Color(50, 50, 50)); // Left Eye
  pixels.setPixelColor(19, pixels.Color(50, 50, 50)); // Right Eye
  for (int i = 0; i < NUMPIXELS - 2; i++) {
    pixels.setPixelColor(i, pixels.Color(DEFAULT_R, DEFAULT_G, DEFAULT_B)); 
  }
  pixels.show();
  return STATE_MONSTER_UNVULNERABLE;
}

int countdown;

int handleEating() {

  pixels.setPixelColor(18, pixels.Color(255, 0, 0)); // Left Eye
  pixels.setPixelColor(19, pixels.Color(255, 0, 0)); // Right Eye
  for (int i = 0; i < NUMPIXELS - 2; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  countdown = millis() + 1000;
  Serial.println(countdown);
  return STATE_FEASTING;
}

int handleFeasting() {
  if (millis() > countdown) {
    Serial.println(millis());
    Serial.println(countdown);
    //delay(10000);
    return STATE_PACMAN_DEFAULT;
  }
  else {
    return STATE_FEASTING;
  }
}

int vRedVal = 0;
int vRedDir = 2;
int vRedCount = 0;

int handleEaten() {
  pixels.setPixelColor(18, pixels.Color(50, 50, 50)); // Left Eye
  pixels.setPixelColor(19, pixels.Color(50, 50, 50)); // Right Eye
  for (int i = 0; i < NUMPIXELS - 2; i++) {
    pixels.setPixelColor(i, pixels.Color(vRedVal > 127 ? 255 : 0, 0, 0)); 
  }
  pixels.show();
  vRedVal+= vRedDir;
  if(vRedVal <= 0 || vRedVal >= 255) {
    vRedDir *= -1;
  }
  vRedCount++;
  if((vRedCount+1) % 800 == 0) {
    allOff();
    return STATE_PACMAN_DEFAULT;
  }
  else {
    return STATE_PACMAN_EATEN;
  }
}

void mirfSetup() {
  Mirf.spi = &MirfHardwareSpi;
  Mirf.cePin = 7;
  Mirf.csnPin = 8;
  Mirf.init();
  Mirf.setRADDR((byte *)"movab");
  Mirf.payload = PAYLOAD_SIZE;
  Mirf.config();
  Serial.println("Listening...");
}


void mirfUpdate() {
  if (!Mirf.isSending() && Mirf.dataReady()) {
    Serial.println("got packet");
    Mirf.getData(payload);
    if (payload[0] == MY_ID) {
      Serial.println("oh my, it's for me!");
      if (payload[1] > 0 && payload[1] < 10) {
        state = payload[1];
        Serial.print("and it even carries a valid new state: "); Serial.println(state);
      }
    }
  }
}

void allOff() {
  // eyes
  pixels.setPixelColor(18, 0); // Left Eye
  pixels.setPixelColor(19, 0); // Right Eye
  //Body lights
  for (int i = 0; i < NUMPIXELS - 2; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
  
}

