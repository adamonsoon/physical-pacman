#include <Servo.h>
#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//  #include <avr/power.h>
//#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(9);
  myservo.write(80);// attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
   pixels.begin();

}

void loop() {
int i=NUMPIXELS;
   pixels.setPixelColor(NUMPIXELS, pixels.Color(255, 0, 0)); // Left Eye


    int angle = 0;
    for (angle = 80; angle > 0; angle--) {
      myservo.write(0);
      delay(3);
    }
    // now scan back from 180 to 0 degrees
    for (angle = 0; angle < 80; angle++)
    {
      myservo.write(angle);

      delay(3);
    }
     pixels.show();

 //   Serial.println (angle);
  }
