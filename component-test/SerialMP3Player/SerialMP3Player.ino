#include <SoftwareSerial.h>
#include <serial_mp3.h>

// connect Arduino pin 5 to MP3 Player's TX pin
// connect Arduino pin 6 to MP3 Player's RX pin

void setup() {
  Serial.begin(9600);
  Serial.println("initializing");
  serialmp3_init();
  serialmp3_set_vol(31);
  
  delay(1000);
  int folder = 1;
  
  for(int song = 1; song <= 4; ++song) {
    Serial.print("playing track #"); Serial.println(song);
    serialmp3_play(folder, song); // on SD Card: /01/003xxx.mp3
    delay(3000);
    serialmp3_stop();
  }

// other commands:  

//  serialmp3_set_vol();
//  serialmp3_prev();
//  serialmp3_next();
//  serialmp3_pause();
//  serialmp3_resume();
}

void loop() {
}

