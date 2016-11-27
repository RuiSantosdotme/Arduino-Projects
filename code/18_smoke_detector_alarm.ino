/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

int redLed = 5;
int greenLed = 8;

int buzzer = 2;
int button = 3;

int smokeSensor = A5;
int sensorThres = 100;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(button) == HIGH) {  
    int sensorValue = analogRead(smokeSensor);
    Serial.println(sensorValue);

    if(sensorValue > sensorThres) {
      tone(buzzer, 1000);
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
    }
    
    else {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      noTone(buzzer);
    }
    delay(10);
  }
  else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    noTone(buzzer);
  }
}
