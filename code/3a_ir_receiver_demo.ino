#include <IRremote.h>

const int RECV_PIN = 11;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Initialize the receiver
}

void loop() {
  if (IrReceiver.decode()) { // Check if data is received
    // Filter out unknown protocols
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      IrReceiver.resume(); // Resume receiving for the next signal
      return; // Skip this loop iteration
    }

    // Print only valid data
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line

    IrReceiver.resume(); // Resume receiving for the next signal
  }
  delay(100);
}
