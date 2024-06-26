#include "arduino_secrets.h"

/*

*/

const int LED = 2;
const int METER = A0;

const int X_PULLDOWN = 8;
const int Y_PULLUP = 9; 

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(X_PULLDOWN, INPUT);
  pinMode(Y_PULLDOWN, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  int read = analogRead(METER);
  
  Serial.println(read);
  
  /*
  if(read < 500) {
    digitalWrite(LED, HIGH); //led turns on
  }
  else {
    digitalWrite(LED, LOW); //led turns off
  }
  delay(500);
  */
  
  if (digitalRead(X_PULLDOWN) == LOW) {
    digitalWrite(LED, HIGH); //what....
  }
}
