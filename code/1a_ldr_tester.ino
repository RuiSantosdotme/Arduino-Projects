/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
*/

// You might need to change the threshold value to find a suitable value
// to turn the LEDs on and off when you move your hand over the photoresistor
int threshold = 600;

// Connect the LED to digital pin 9
int led = 9;

// The photoresistor lead is connected to analog pin 0
int sensor = A0;
// stores the analog reading value
int sensorValue = 0;

void setup() {
  // sets the LED as an output
  pinMode(led, OUTPUT);
  // sets the photoresistor as an input
  pinMode(sensor, INPUT);
  // starts the serial communication at a baud rate of 9600
  Serial.begin(9600);
}

void loop(){
  // Reads the current photoresistor value
  sensorValue = analogRead(sensor);
  // if the value is below a certain threshold it turns the LED on, otherwise the LED remains off
  if (sensorValue < threshold) {
      digitalWrite(led, HIGH);
  }
  else {
      digitalWrite(led,LOW);
  }
  // prints the current readings in the Arduino IDE serial monitor
  Serial.print ("Sensor reading: ");
  Serial.println(sensorValue);
  delay(50);
}
