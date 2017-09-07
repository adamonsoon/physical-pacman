int startPin = 4;
int endPin = 11;

int onDelay = 100;
int offDelay = 200;

bool withPrev = true;

void setup() {
  for (int i = startPin; i < endPin; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
   
  for (int i = startPin; i < endPin; i++) {
    toggleMagnets(i, false);
  }
  
  for (int i = (endPin - 2); i > startPin; i--) {
    toggleMagnets(i, true);
  }
}

void toggleMagnets(int i, bool isDown) {
  setPinState(i, HIGH, isDown);
  delay(onDelay);

  setPinState(i, LOW, isDown);
  delay(offDelay);  
}

void setPinState(int pin, bool state, bool isDown) {
  
  digitalWrite(pin, !state);
 
  if (!(pin == startPin) && withPrev) {
    if (isDown) {
      digitalWrite(pin - 1, !state);      
    } else {
      digitalWrite(pin + 1, !state);
    }
  }
}
