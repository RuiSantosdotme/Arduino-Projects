/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

#include <LiquidCrystal.h>

// Preparing LCD connections
LiquidCrystal lcd(4, 3, 5, 6, 7, 8);

// Start and pause buttons
int start = 9;
int pause = 10;

// Variables to store start time, current time and time passed in seconds
double startTime = millis();
double currentTime = 0;
double timeInSeconds = 0;

void setup(){
  // Starting a 16x2 character LCD
  lcd.begin(16, 2);
  lcd.clear();

  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("Stopwatch");
  lcd.setCursor(0, 1);
  lcd.print("Press play!");
  
  //Serial.begin(9600);
  
  // Preparing buttons as INPUTs
  pinMode(start, INPUT);
  pinMode(pause, INPUT);
}

void loop(){
  // When start button is pressed, it starts counting time
  if (digitalRead(start) == LOW){
    lcd.clear();
    startTime = millis();
    // While pause button is not pressed it keeps counting
    while (digitalRead(pause) == HIGH){
      currentTime = millis();
      timeInSeconds = (currentTime - startTime) / 1000;
      lcd.setCursor(0, 0);
      lcd.print("Stopwatch");
      lcd.setCursor(0, 1);
      lcd.print(timeInSeconds);
      lcd.setCursor(9, 1);
      lcd.print("seconds");
      // Serial.println(timeInSeconds);
      delay(100);
    }
    // When pause button is pressed, it pauses timer
    if (digitalRead(pause) == LOW){
      lcd.setCursor(0, 0);
      lcd.print("Stopwatch");
      lcd.setCursor(0, 1);
      lcd.print(timeInSeconds);
      lcd.setCursor(9, 1);
      lcd.print("seconds");
      delay(100);
    }
  }
}
