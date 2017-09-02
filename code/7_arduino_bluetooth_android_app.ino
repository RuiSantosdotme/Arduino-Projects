/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

#include <DHT.h>

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int ledOn = 7;
int ledPWM = 6;

int state;
int flag = 0;      //makes sure that the serial only prints once the state

unsigned long previousMillis = 0;
const long interval = 5000;

void displayTempHumid() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.print(" ");
    Serial.println("Failed to read");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");
  Serial.print("Temperature: ");
  Serial.print(f);
  Serial.println(" F");
}

void setup() {
  // sets the pins as outputs:
  pinMode(ledOn, OUTPUT);
  pinMode(ledPWM, OUTPUT);

  digitalWrite(ledOn, LOW);
  analogWrite(ledPWM, LOW);

  dht.begin(); // initialize dht

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  
  //if some date is sent, reads it and saves in state
  if (Serial.available() > 0) {
    state = Serial.read();
    flag = 0;
  }
  // if the state is ON the LED is ON
  if (state == 'F' && flag == 0) {
    digitalWrite(ledOn, HIGH);
    flag = 1;
  }
  // if the state is OFF the LED is OFF
  else if (state == 'N' && flag == 0) {
    digitalWrite(ledOn, LOW);
    flag = 1;
  }
  else if (state != 'N' && state != 'F' && flag == 0) {
    analogWrite(ledPWM, state);
    flag = 1;
  }
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    displayTempHumid();
  }
}
