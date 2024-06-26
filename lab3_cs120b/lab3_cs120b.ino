#include "arduino_secrets.h"

int red_pin = 9;
int blue_pin = 10;
int green_pin = 11;

//you will need to determine the value for dark
//its unique to the lighting in your room
int dark_threshold = 70;

void turnOff(){
  analogWrite(red_pin, 0);
  analogWrite(blue_pin, 0);
  analogWrite(green_pin, 0);
}

void turnWhite() {
  analogWrite(red_pin, 255);
  analogWrite(blue_pin, 255);
  analogWrite(green_pin, 255);
}

int color_index = 0;

void colorDial() {
  color_index = map(analogRead(A0), 0, 1023, 0, 5);

  //white, red, purple, blue, orange, green
  int r_colors[] = {255,  255,    255,  0,    255,    0}; 
  int g_colors[] = {255,  0,  0,    0,    255,    255};
  int b_colors[] = {255,  0,  255,  255,  0,      0};

  analogWrite(red_pin, r_colors[color_index]);
  analogWrite(blue_pin, b_colors[color_index]);
  analogWrite(green_pin, g_colors[color_index]);
}

enum buttonStates{INIT, waiting, on} currState;

void SM_Colors() {
  switch(currState) { 
    case INIT:
      turnOff();

      currState = waiting;
      break;
    case waiting:
      turnOff();

      if (analogRead(A1) > dark_threshold) {
        currState = waiting;
      }
      else {
        currState = on;
      }
      break;
    case on:
      //turnWhite();
      colorDial();

      if (analogRead(A1) <= dark_threshold) {
        currState = on;
      }
      else {
        currState = waiting;
      }
      break;
  }//end switch

} //end SM_Colors

void setup() {
  // put your setup code here, to run once:
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  Serial.begin(9600);
  currState = INIT;
}

void loop() {
  // put your main code here, to run repeatedly:
  //potentiometer(A0) and the photoresistor(A1)
  Serial.print(analogRead(A0));
  Serial.print(' ');
  Serial.print(analogRead(A1));
  Serial.print(' ');
  Serial.println(color_index);
  
  SM_Colors(); 
}