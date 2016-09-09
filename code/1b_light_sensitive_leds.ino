/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
*/

// You might need to change the threshold value to find a suitable value
// to turn the LEDs on and off when you move your hand over the photoresistor
int threshold = 600;

// Connect the LEDs from digital pin 7 to digital pin 2
int led1 = 7;
int led2 = 6;
int led3 = 5;
int led4 = 4;
int led5 = 3;
int led6 = 2;

// Connect photoresistor leads are connected from analog 0 to analog 5
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;

// stores the analog reading values for each photoresistor
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;
int sensorValue6 = 0;

void setup() {
  // sets the LEDs as an output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  // sets the photoresistors as an input
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
  // starts the serial communication at a baud rate of 9600
  // Serial.begin(9600);
}

void loop(){
  // Reads the current photoresistor value
  sensorValue1 = analogRead(sensor1);
  // if the value is below a certain threshold it turns the LED on, otherwise the LED remains off
  // This process is repeated for all photoresistors and LEDs
  if (sensorValue1 < threshold) {
      digitalWrite(led1, HIGH);
  }
  else {
      digitalWrite(led1,LOW);
  }
  sensorValue2 = analogRead(sensor2);
  if (sensorValue2 < threshold) {
      digitalWrite(led2, HIGH);
  }
  else {
      digitalWrite(led2,LOW);
  }
  
  sensorValue3 = analogRead(sensor3);
  if (sensorValue3 < threshold) {
      digitalWrite(led3, HIGH);
  }
  else {
      digitalWrite(led3,LOW);
  }
  
  sensorValue4 = analogRead(sensor4);
  if (sensorValue4 < threshold) {
      digitalWrite(led4, HIGH);
  }
  else {
      digitalWrite(led4,LOW);
  }
  sensorValue5 = analogRead(sensor5);
  if (sensorValue5 < threshold) {
      digitalWrite(led5, HIGH);
  }
  else {
      digitalWrite(led5,LOW);
  }
  sensorValue6 = analogRead(sensor6);
  if (sensorValue6 < threshold) {
      digitalWrite(led6, HIGH);
  }
  else {
      digitalWrite(led6,LOW);
  }
  // You can uncomment for debugging purporses
  //Serial.print ("Sensor reading: ");
  //Serial.println(sensorValue1);
  delay(50);
}
