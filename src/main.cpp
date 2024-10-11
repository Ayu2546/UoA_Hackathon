#include <Arduino.h>

const int SR = 2; // Red switch
const int SY = 3; // Yellow switch
const int SW = 4; // White switch
const int SG = 5; // Green switch
const int SB = 6; // Blue switch

const int RL = A0; // Variable resistor on the left
const int RR = A1; // Variable resistor on the right

String str;
boolean red, yellow, white, green, blue;
int left, right, scaledLeft, scaledRight;

// Determining if switches have been pressed
void output(boolean, boolean, boolean, boolean, boolean);

// Setput serial communication and pins 
void setup() {
  Serial.begin(115200);

  pinMode(SR, INPUT);
  pinMode(SY, INPUT);
  pinMode(SW, INPUT);
  pinMode(SG, INPUT);
  pinMode(SB, INPUT);

  pinMode(RL, INPUT);
  pinMode(RR, INPUT);
}

// The main operation
void loop() {
  str = "";

  red = digitalRead(SR);
  yellow = digitalRead(SY);
  white = digitalRead(SW);
  green = digitalRead(SG);
  blue = digitalRead(SB);
  
  left = analogRead(RL);
  right = analogRead(RR); 

  scaledLeft = map(left, 0, 1023, 0, 100);
  scaledRight = map(right, 0, 1023, 0, 100);

  output(red, yellow, white, green, blue);

  Serial.println(str + "|" + String(scaledLeft) + "|" + String(scaledRight));

  delay(10);
}

void output(boolean red, boolean yellow, boolean white, boolean green, boolean blue) {
  if(red == HIGH) {
    str += "R,";
  } 

  if(yellow == HIGH) {
    str += "Y,";
  } 

  if(white == HIGH) {
    str += "W,";
  } 

  if(green == HIGH) {
    str += "G,";
  } 
  
  if(blue == HIGH) {
    str += "B,";
  }

  if(str.endsWith(",")) {
    str = str.substring(0, str.length() - 1);
  }

  if(str.length() == 0) {
    str = "NONE";
  }

  return;
}