#include "arduino_secrets.h"

int x = 6; //left button
int y = 7; //right button

int num = 750;

int B[4] = {2, 3, 4, 5}; //we are only considering pins 2, 3, 4, and 5

void setup() {

  // put your setup code here, to run once:

  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
  }
  Serial.begin(9600);
}

void flash() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(B[i], HIGH);
  }
  delay(500);
  for (int i = 0; i < 4; i++) {
    digitalWrite(B[i], LOW);
  }
  delay(500);
  Serial.println(analogRead(A0));
}

void loop() {

  flash();

}