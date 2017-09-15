#include <SoftwareSerial.h>
#include <Arduino.h>


//should connect to TX of the Serial MP3 Player module
#ifndef ARDUINO_RX
#define ARDUINO_RX   5
#endif
//connect to RX of the module
#ifndef ARDUINO_TX
#define ARDUINO_TX   6
#endif


#define SERIAL_MP3_NO_RESPONSE 0
#define SERIAL_MP3_UNKNOWN_RESPONSE 10
#define SERIAL_MP3_MEMORY_CARD_INSERTED 20
#define SERIAL_MP3_TRACK_COMPLETE 30
#define SERIAL_MP3_TRACK_PLAYING 40
#define SERIAL_MP3_ACK 50

#define CMD_SEL_DEV 0X09
  #define DEV_TF 0X02

#define CMD_SET_DAC 0X1A
  #define DAC_ON  0X00
  #define DAC_OFF 0X01

#define CMD_VOLUME_UP 0X04
#define CMD_VOLUME_DOWN 0X05
#define CMD_SET_VOLUME 0X06

#define CMD_PLAY 0X0D
#define CMD_PLAY_W_INDEX 0X08
#define CMD_PLAY_W_VOL 0X22
#define CMD_PLAY_FOLDER_FILE 0X0F
#define CMD_STOP_PLAY 0X16
#define CMD_PAUSE 0X0E
#define CMD_SINGLE_CYCLE_PLAY 0X08
#define CMD_SINGLE_CYCLE 0X19
  #define SINGLE_CYCLE_ON 0X00
  #define SINGLE_CYCLE_OFF 0X01

#define CMD_NEXT_SONG 0X01
#define CMD_PREV_SONG 0X02

#define CMD_SLEEP_MODE 0X0A
#define CMD_WAKE_UP 0X0B
#define CMD_RESET 0X0C

#define CMD_FOLDER_CYCLE 0X17
#define CMD_SHUFFLE_PLAY 0X18

#define CMD_GROUP_DISPLAY 0X21

SoftwareSerial mp3_serial(ARDUINO_RX, ARDUINO_TX);

static int8_t serialmp3_sendbuf[8] = { 0 };
// answer buffer
static uint8_t serialmp3_ansbuf[10] = {0};
// flag for playing
boolean serialmp3_isPlaying = false;


void serialmp3_sendCommand(int8_t command, int16_t dat) {
  delay(20);
  serialmp3_sendbuf[0] = 0x7e; //starting byte
  serialmp3_sendbuf[1] = 0xff; //version
  serialmp3_sendbuf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  serialmp3_sendbuf[3] = command; //
  serialmp3_sendbuf[4] = 0x01; //0x00 = no feedback, 0x01 = feedback
  serialmp3_sendbuf[5] = (int8_t)(dat >> 8);//datah
  serialmp3_sendbuf[6] = (int8_t)(dat); //datal
  serialmp3_sendbuf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++) {
    mp3_serial.write(serialmp3_sendbuf[i]) ;
  }
}

String serialmp3_sbyte2hex(uint8_t b) {
  String shex;
  shex = "0X";

  if (b < 16) shex += "0";
  shex += String(b, HEX);
  shex += " ";
  return shex;
}

byte serialmp3_incomingPointer = 0;
String serialmp3_answer = "";

int serialmp3_checkStatus() {
  if(!mp3_serial.available()) {
    return SERIAL_MP3_NO_RESPONSE;
  }
  int result = SERIAL_MP3_UNKNOWN_RESPONSE;
  uint8_t b = mp3_serial.read();
  if (b == 0x7E) {
    serialmp3_incomingPointer = 0;
    serialmp3_answer = "";
  }
  serialmp3_ansbuf[serialmp3_incomingPointer] = b;
  serialmp3_incomingPointer++;
  serialmp3_answer += serialmp3_sbyte2hex(b);
  if (b == 0xef) {
    switch (serialmp3_ansbuf[3]) {
      case 0x3A:
        serialmp3_answer += " -> Memory card inserted.";
        result = SERIAL_MP3_MEMORY_CARD_INSERTED;
        break;

      case 0x3D:
        serialmp3_isPlaying = false;
        serialmp3_answer += " -> Completed play num " + String(serialmp3_ansbuf[6], DEC);
        result = SERIAL_MP3_TRACK_COMPLETE;
        break;

      case 0x4C:
        serialmp3_answer += " -> Playing: " + String(serialmp3_ansbuf[6], DEC);
        result = SERIAL_MP3_TRACK_PLAYING;
        break;

      case 0x41:
        serialmp3_answer += " -> Data recived correctly. ";
        result = SERIAL_MP3_ACK;
        break;
    } //end switch
    //Serial.println(serialmp3_answer);
  } //end if
  //Serial.println(result);
  if(result == SERIAL_MP3_UNKNOWN_RESPONSE) {
    // Serial.print("SERIAL_MP3_UNKNOWN_RESPONSE("); Serial.print(b); Serial.println(")");
  }
  return result;
} 


void serialmp3_init() {
  mp3_serial.begin(9600);
  //Wait chip initialization is complete
  delay(500);
  //wait for 200ms
  serialmp3_sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
  delay(200);
}

void serialmp3_set_vol(byte vol) {
  serialmp3_sendCommand(CMD_SET_VOLUME, vol);
}

void serialmp3_play(byte folder, byte track, boolean wait) {
  //play the first song with volume 15 class: 0X0F01
  // serialmp3_sendCommand(CMD_PLAY_W_VOL, int(volume<< 8) | track);
  serialmp3_sendCommand(CMD_PLAY_FOLDER_FILE, folder<<8 | track); //>>>
  if(wait) {
    while(serialmp3_checkStatus() != SERIAL_MP3_TRACK_COMPLETE) {
      delay(2);
    }
  }
}

void serialmp3_play(byte track) {
  serialmp3_play(1, track, false);
}

void serialmp3_play(byte folder, byte track) {
  serialmp3_play(folder, track, false);
}

void serialmp3_stop() {
  serialmp3_sendCommand(CMD_STOP_PLAY, 0);
}

void serialmp3_pause() {
  serialmp3_sendCommand(CMD_PAUSE, 0);
}

void serialmp3_resume() {
  serialmp3_sendCommand(CMD_PLAY, 0);
}

void serialmp3_next() {
  serialmp3_sendCommand(CMD_NEXT_SONG, 0);
}

void serialmp3_prev() {
  serialmp3_sendCommand(CMD_PREV_SONG, 0);
}


