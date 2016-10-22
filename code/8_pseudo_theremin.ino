/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

int speakerPin = 12;
int photocellPin = A0;
 
void setup(){
  pinMode(speakerPin, OUTPUT);
}
 
void loop(){
  int reading = analogRead(photocellPin);
  int pitch = 200 + reading / 2;
  tone(speakerPin, pitch);
}
