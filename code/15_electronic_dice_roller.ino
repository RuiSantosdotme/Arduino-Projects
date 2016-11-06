/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

#include "LedControl.h"
#include "binary.h"

/*
 * Define pins for the LED matrix
 * DIN connects to pin 12
 * CLK connects to pin 11
 * CS connects to pin 10 
 */
LedControl lc=LedControl(12,11,10,1);

//defining binary patterns for each number
byte zero[] = {
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000};

byte one[] = {
B00000000,
B00000000,
B00000000,
B00011000,
B00011000,
B00000000,
B00000000,
B00000000};

byte two[] ={
B00000000,
B01100000,
B01100000,
B00000000,
B00000000,
B00000110,
B00000110,
B00000000};

byte three[]={
B11000000,
B11000000,
B00000000,
B00011000,
B00011000,
B00000000,
B00000011,
B00000011};

byte four[]={
B00000000,
B01100110,
B01100110,
B00000000,
B00000000,
B01100110,
B01100110,
B00000000};

byte five[]={
B11000011,
B11000011,
B00000000,
B00011000,
B00011000,
B00000000,
B11000011,
B11000011};

byte six[]={
B00000000,
B11011011,
B11011011,
B00000000,
B00000000,
B11011011,
B11011011,
B00000000};

int buttonPin = 8;

int result = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,8);
  // Clear the display
  lc.clearDisplay(0); 
}

void loop() {
  if (digitalRead(buttonPin)){
    rollDice();
  }
  delay(50);
}

void rollDice(){
  int result = 0;
  int timeDiceRolls = random(10, 15);
  for(int i=0; i<timeDiceRolls; i++){
    // result variable will be 1 to 6
    result = random(1, 7); 
    printResult(result);
    delay(100 + i * 10);
  }
  for(int i=0; i<2; i++){
    printResult(0);
    delay(500);
    printResult(result);
    delay(500);
  }
}

void printResult(int result){
  if(result==0){
    lc.setRow(0,0,zero[0]);
    lc.setRow(0,1,zero[1]);
    lc.setRow(0,2,zero[2]);
    lc.setRow(0,3,zero[3]);
    lc.setRow(0,4,zero[4]);
    lc.setRow(0,5,zero[5]);
    lc.setRow(0,6,zero[6]);
    lc.setRow(0,7,zero[7]);
  }
  else if(result==1){
    lc.setRow(0,0,one[0]);
    lc.setRow(0,1,one[1]);
    lc.setRow(0,2,one[2]);
    lc.setRow(0,3,one[3]);
    lc.setRow(0,4,one[4]);
    lc.setRow(0,5,one[5]);
    lc.setRow(0,6,one[6]);
    lc.setRow(0,7,one[7]);
  }
  else if(result==2){
    lc.setRow(0,0,two[0]);
    lc.setRow(0,1,two[1]);
    lc.setRow(0,2,two[2]);
    lc.setRow(0,3,two[3]);
    lc.setRow(0,4,two[4]);
    lc.setRow(0,5,two[5]);
    lc.setRow(0,6,two[6]);
    lc.setRow(0,7,two[7]);
  }
  else if(result==3){
    lc.setRow(0,0,three[0]);
    lc.setRow(0,1,three[1]);
    lc.setRow(0,2,three[2]);
    lc.setRow(0,3,three[3]);
    lc.setRow(0,4,three[4]);
    lc.setRow(0,5,three[5]);
    lc.setRow(0,6,three[6]);
    lc.setRow(0,7,three[7]);
  }
  else if(result==4){
    lc.setRow(0,0,four[0]);
    lc.setRow(0,1,four[1]);
    lc.setRow(0,2,four[2]);
    lc.setRow(0,3,four[3]);
    lc.setRow(0,4,four[4]);
    lc.setRow(0,5,four[5]);
    lc.setRow(0,6,four[6]);
    lc.setRow(0,7,four[7]);
  }
  else if(result==5){
    lc.setRow(0,0,five[0]);
    lc.setRow(0,1,five[1]);
    lc.setRow(0,2,five[2]);
    lc.setRow(0,3,five[3]);
    lc.setRow(0,4,five[4]);
    lc.setRow(0,5,five[5]);
    lc.setRow(0,6,five[6]);
    lc.setRow(0,7,five[7]);
  }
  else if(result==6){
    lc.setRow(0,0,six[0]);
    lc.setRow(0,1,six[1]);
    lc.setRow(0,2,six[2]);
    lc.setRow(0,3,six[3]);
    lc.setRow(0,4,six[4]);
    lc.setRow(0,5,six[5]);
    lc.setRow(0,6,six[6]);
    lc.setRow(0,7,six[7]);
  }
  Serial.print(result);
}
