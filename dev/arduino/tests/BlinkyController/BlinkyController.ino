#define STATE_IDLE 0
#define STATE_OFF 5
#define STATE_DEFAULT 10
#define STATE_VULNERABLE 20
#define STATE_EATING 30
#define STATE_FEASTING 35
#define STATE_EATEN 40

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

int state = STATE_DEFAULT;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(20);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  switch (state) {
    case STATE_IDLE:
      state = handleIdle();
      break;
    case STATE_OFF:
      state = handleOff();
      break;
    case STATE_DEFAULT:
      state = handleDefault();
      break;
    case STATE_VULNERABLE:
      state = handleVulnerable();
      break;
    case STATE_EATING:
      state = handleEating();
      break;
    case STATE_FEASTING:
      state = handleFeasting();
      break;
    case STATE_EATEN:
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

int handleDefault() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  pixels.setPixelColor(18, pixels.Color(150, 150, 150)); // Left Eye
  pixels.setPixelColor(19, pixels.Color(150, 150, 150)); // Right Eye

  //Body lights
  for (int i = 0; i < NUMPIXELS - 2; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(50, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  if (Serial.available()) {
    return Serial.parseInt();
  }
  else {
    return STATE_DEFAULT;
  }
}

int handleIdle() {
  if (Serial.available()) {
    return Serial.parseInt();
  }
  else {
    return STATE_IDLE;
  }
}

int handleVulnerable() {

}

int countdown;

int handleEating() {

  pixels.setPixelColor(18, pixels.Color(255, 0, 0)); // Left Eye
  pixels.setPixelColor(19, pixels.Color(255, 0, 0)); // Right Eye
 for (int i = 0; i < NUMPIXELS - 2; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  countdown = millis() + 1000;
  return STATE_FEASTING;
  
}

int handleFeasting() {
  if(millis() > countdown) {
    return STATE_OFF;
  }
  else {
    return STATE_FEASTING;
  }
}

int handleEaten() {

}


