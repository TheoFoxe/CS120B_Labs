#include "arduino_secrets.h"

//https://youtube.com/shorts/V6yXxPvFWwk?feature=share

int x = 6;
int y = 7;

int B[4] = {2, 3, 4, 5};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
 }
  Serial.begin(9600);
}

char Patterns[3] = {0x05, 0x02, 0x00};

int B_LEDS[4] = {2,3,4,5};

void clearLEDs(char pattern) {
  for(int i = 0; i < 4; i++) {
     digitalWrite(B[i], 0);
  }
}

void writePattern(char pattern) {
  for(int i = 0; i < 4; i++) {
     digitalWrite(B[i], (pattern & (1 << i)) > 0);
  }
}

int currPattern = 0;
int state = 1;

void loop() {
  writePattern(currPattern);


  switch(state) {
    case 1: //waiting for input
      if (digitalRead(x) == HIGH && digitalRead(y) == LOW && currPattern != 15) {
        state = 2;
      }
      else if (digitalRead(x) == LOW && digitalRead(y) == HIGH && currPattern != 0) {
        state = 4;
      }
      else {
        state = 1;
      }
      break;
    case 2: //x is pushed down
      if (digitalRead(x) == HIGH) {
        state = 2;
      }
      else if (digitalRead(x) == LOW) {
        state = 3;
      }
      break;
    case 3://left shift
      currPattern = (currPattern << 1) | 0x01;
      delay(50);
      state = 1;
      break;

    case 4: //y is pushed down
      if (digitalRead(y) == HIGH) {
        state = 4;
      }
      else if (digitalRead(y) == LOW) {
        state = 5;
      }
      break;
    case 5: //right shift
      currPattern = currPattern >> 1;
      delay(50);
      state = 1;
      break;
      
  }
  

}
