/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

int led1 = 3 ;// define LED 
int led2 = 4;
int led3 = 5;
int led4 = 6;
int led5 = 7;
int led6 = 8;
int led7 = 9;

int sensorPin = 2;
int val = 0; // define numeric variables val
 
void setup (){
  pinMode(led1, OUTPUT) ;// define LED as output 
  pinMode(led2, OUTPUT) ;// define LED as output 
  pinMode(led3, OUTPUT) ;// define LED as output 
  pinMode(led4, OUTPUT) ;// define LED as output 
  pinMode(led5, OUTPUT) ;// define LED as output 
  pinMode(led6, OUTPUT) ;// define LED as output 
  pinMode(led7, OUTPUT) ;// define LED as output 
  pinMode(sensorPin, INPUT) ;// output interface D0 is defined sensor
  Serial.begin(9600);
}
 
void loop (){
  val = digitalRead(sensorPin);
  Serial.println(val);
  // When the sound detection module detects a signal, LED flashes
  if(val== HIGH){ 
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
  }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
  }
}
