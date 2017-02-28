/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
*/

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 111);

// REPLACE THE NEXT VARIABLE WITH YOUR IFTTT MAKER CHANNEL API KEY
String iftttApiKey = "YOUR_MAKER_CHANNEL_API_KEY";

// name address for IFTTT
char server[] = "maker.ifttt.com";

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// the number of the pushbutton pin
const int button = 7;
int lastButtonState = LOW;   // the previous reading from the input pin

// the number of the LED pin
const int led = 8;

// PIR Motion Sensor is connected to D2.
int PIRInterrupt = 2;
int PIRArmed = LOW;

// Timer Variables
long lastDebounceTime = 0;  
long debounceDelay = 10000;
long lastButtonDebounceTime = 0;  
long debounceButtonDelay = 50;

void setup() {
  // button pin configuration
  pinMode(button, INPUT);
  // led pin configuration
  pinMode(led, OUTPUT);
  // PIR motion sensor set as an input
  pinMode(PIRInterrupt, INPUT);
  // Triggers detectMotion function on rising mode to turn the relay on, if the condition is met
  attachInterrupt(digitalPinToInterrupt(PIRInterrupt), detectMotion, RISING);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);

}

void loop() {
   // read the state of the switch into a variable
  int reading = digitalRead(button);

  if ((millis() - lastButtonDebounceTime) > debounceButtonDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != lastButtonState) {
      lastButtonState = reading;
      if(lastButtonState == HIGH) {
        PIRArmed = !PIRArmed;
      }
      digitalWrite(led, PIRArmed);
    }
    lastButtonDebounceTime = millis();
  }
}


void detectMotion() {
  Serial.println("Motion detected");
  if((millis() - lastDebounceTime) > debounceDelay && PIRArmed){
    // stop previous client connection, if still running
    client.stop();
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.print("GET /trigger/detect_motion/with/key/");
      client.print(iftttApiKey);
      client.println(" HTTP/1.1");
      client.println("Host: maker.ifttt.com");
      client.println("Connection: close");
      client.println();
    } 
    else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
    Serial.println("Notification sent");
    lastDebounceTime = millis();
  }
}

