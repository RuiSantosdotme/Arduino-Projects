/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

const int motor1Pin1 = 3; // pin 2 on L293D IC
const int motor1Pin2 = 4; // pin 7 on L293D IC
const int enable1Pin = 6; // pin 1 on L293D IC
const int motor2Pin1 = 8; // pin 10 on L293D IC
const int motor2Pin2 = 9; // pin 15 on L293D IC
const int enable2Pin = 11; // pin 9 on L293D IC

// My right sensor might be YOUR left sensor
const int rightSensor = A0; 
const int leftSensor = A1;

// Variable definitions
int leftSensorValue; 
int rightSensorValue; 
int sensorDifferenceValue;

// Threshold Value for the sensor difference
const int thresholdValueDifference = 75;

void setup() {
  // Setting outputs and inputs
  pinMode(enable2Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT); 
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT); 
  // Serial debugging at 9600 baud rate
  Serial.begin(9600); 
}

void loop() { 
  // Reads LDR sesnsors and calculates the differences
  leftSensorValue = 1023-analogRead(leftSensor);
  rightSensorValue = 1023-analogRead(rightSensor); 
  sensorDifferenceValue = abs(leftSensorValue-rightSensorValue);

  // Prints the current readings
  Serial.print("Left Sensor = ");
  Serial.print(leftSensorValue);
  Serial.print(" - Right Sensor = ");
  Serial.println(rightSensorValue);

  // Turns the robot Left, if the light is currently higher in the Left LDR
  if (leftSensorValue > rightSensorValue && 
    sensorDifferenceValue > thresholdValueDifference){ 
    analogWrite(enable2Pin, 255);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    analogWrite(enable1Pin, 255);
    digitalWrite( motor1Pin2, HIGH);
    digitalWrite( motor1Pin1, LOW);
    Serial.println("Left");
    delay(100);
  }
  // Turns the robot Right if the light is currently higher in the Right LDR
  if (leftSensorValue < rightSensorValue && 
    sensorDifferenceValue > thresholdValueDifference){ 
    analogWrite(enable2Pin, 255);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(enable1Pin, 255);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor1Pin1, HIGH);
    Serial.println("Right");
    delay(100);
  }
  // Goes forward if the difference between the two is not relevant
  else if (sensorDifferenceValue < thresholdValueDifference){
    analogWrite(enable2Pin, 255);   
    digitalWrite(motor2Pin1, HIGH); 
    digitalWrite(motor2Pin2, LOW);  
    analogWrite(enable1Pin, 255);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor1Pin1, LOW);   
    Serial.println("Forward");
    delay(100);
  }
}
