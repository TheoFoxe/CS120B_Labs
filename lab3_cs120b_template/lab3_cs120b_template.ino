#include "arduino_secrets.h"

int red_pin = 9;
int blue_pin = 10;
int green_pin = 11;

//you will need to determine the value for dark
//its unique to the lighting in your room
int dark_threshold = 70;

void turnoff(){
  analogWrite(red_pin, 0);
  analogWrite(blue_pin, 0);
  analogWrite(green_pin, 0);
}

enum ButtonStates{INIT,off, on} current_state;
void SM0_Tick() {
   // State Transistions
   switch(current_state) {
       case INIT:
         current_state = off;
         break;
       case off:
         current_state = on;
         break;
       case on:
         current_state = off;
         break;
       default:
         current_state = off;
         break;
   }
   // State Actions
   switch(current_state) {
   	case INIT:
      break;
    case off:
      turnoff();
      break;
    case on:
   //displays the color white
      analogWrite(red_pin, 255);
       analogWrite(green_pin, 255);
       analogWrite(blue_pin, 255);
      break;
   	default:
      break;
   }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  Serial.begin(9600);
  current_state = INIT;
}
void loop() {
  // put your main code here, to run repeatedly:
  SM0_Tick();
  //you can delete these prints if you want they are 
  //just here to show you the values of the 
  //potentiometer(A0) and the photoresistor(A1)
  //Serial.print(analogRead(A0));
  //Serial.print(' ');
  //Serial.println(analogRead(A1));
  //DELETE THIS LINE OF CODE WHEN YOU MAKE YOUR SOLUTION
  //delay(500); //DELETE ME!!!!!
  //PLEASE DONT FORGET TO DELETE THE DELAY FUNCTION
  //its only there so you can see the transition from states
  //and so that your serial monitor is not spammed with values
}
