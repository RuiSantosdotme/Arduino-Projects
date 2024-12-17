/*
 * Modified by Rui Santos, http://randomnerdtutorialscom
 * based on IRremote Library - Ken Shirriff
*/
 
#include <IRremote.h>

const int RECV_PIN = 11;

const int bluePin = 10;
const int greenPin = 9;
const int yellowPin = 8;

void setup() {
  Serial.begin(9600); // Start serial communication
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Start the receiver

  pinMode(bluePin, OUTPUT);    // Set the pins as output
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
}

void loop() {
  // Decode the infrared input
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      IrReceiver.resume(); // Resume receiving for the next signal
      return; // Skip this loop iteration
    }

    // Print the received command for debugging
    IrReceiver.printIRResultShort(&Serial);

    switch (IrReceiver.decodedIRData.command) {
      case 0x01: // Command to turn ON the blue LED
        digitalWrite(bluePin, HIGH);
        Serial.println("Blue LED ON");
        break;

      case 0x02: // Command to turn ON the green LED
        digitalWrite(greenPin, HIGH);
        Serial.println("Green LED OFF");
        break;

      case 0x03: // Command to turn ON the yellow LED
        digitalWrite(yellowPin, HIGH);
        Serial.println("Yellow LED ON");
        break;

      case 0x04: // Command to turn ON the yellow LED
        digitalWrite(bluePin, LOW);
        Serial.println("Blue LED OFF");
        break;

      case 0x05: // Command to turn ON the yellow LED
        digitalWrite(greenPin, LOW);
        Serial.println("Green LED OFF");
        break;

      case 0x06: // Command to turn ON the yellow LED
        digitalWrite(yellowPin, LOW);
        Serial.println("Yellow LED OFF");
        break;

      default: // Unknown command
        Serial.println("Unknown Command");
        break;
    }

    IrReceiver.resume(); // Receive the next value
  }
  delay(10);
}
