#define PIN_COUNT 8
#define EVENT_FREQUENCY 100

int pins[] = {4,5,6,7,8,9,10,11};

int onDelay = 100;
int offDelay = 100;

int pos = 0;
int dir = 1;

void setup() {
  for (int i = 0; i < PIN_COUNT; i++) {
    pinMode(pins[i], OUTPUT);
  }
  Serial.begin(9600);
}

int lastEvent = 0;

void loop() {
  if(millis()-lastEvent > EVENT_FREQUENCY) {
    pos = (pos + dir);
    if(pos == PIN_COUNT & dir == 1) {
      pos = PIN_COUNT-1;
      dir *= -1;
    }
    if(pos == 0 && dir == -1) {
      pos = 1;
      dir *= -1;
    }
    lastEvent = millis();
    Serial.println(String(pos) + " " + dir);
    for(int i = 0; i < PIN_COUNT; ++i) digitalWrite(pins[i],HIGH); //clear all
    digitalWrite(pins[pos], LOW);
    if(dir>0) digitalWrite(pins[pos-1], LOW);
    else digitalWrite(pins[pos+1], LOW);
  }
}
