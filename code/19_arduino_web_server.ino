/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
*/

#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 2

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 111);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

// Relay state and pin
String relay1State = "Off";
const int relay = 7;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Client variables 
char linebuf[80];
int charcount=0;
boolean authentificated=false;

void setup() { 
  // Start up the sensors library
  sensors.begin(); 
  // Relay module prepared 
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  
  // Open serial communication at a baud rate of 9600
  Serial.begin(9600);
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

// Display dashboard page with on/off button for relay
// It also print Temperature in C and F
void dashboardPage(EthernetClient &client) {
  client.println("<!DOCTYPE HTML><html><head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">");                                                                    
  client.println("<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\"></script>");                                                               
  client.println("</head><div class=\"container\">");
  client.println("<h1>Arduino Web Server - <a href=\"/\">Refresh</a></h1>");
  // Generates buttons to control the relay
  client.println("<h2>Relay 1 - State: " + relay1State + "</h2><div class=\"row\">");
  // If relay is off, it shows the button to turn the output on          
  if(relay1State == "Off"){
    client.println("<div class=\"col-md-2\"><a href=\"/relay1on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div></div>");
  }
  // If relay is on, it shows the button to turn the output off         
  else if(relay1State == "On"){
    client.println("<div class=\"col-md-2\"><a href=\"/relay1off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div></div>");                                                                    
  }
  // Displays temperature in C and F
  client.println("<h2>Temperature</h2><div class=\"col-md-2\"><h3>");
  sensors.requestTemperatures();
  client.print(sensors.getTempCByIndex(0));
  client.print(" deg C ");
  client.print(sensors.getTempFByIndex(0));
  client.print(" deg F</h3></div>");
  client.println("</div></body></html>"); 
}

// If login fails, display 401 page
void failedLoginPage(EthernetClient &client){
  client.println("HTTP/1.1 401 Authorization Required");
  client.println("WWW-Authenticate: Basic realm=\"Secure Area\"");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE html><html>");
  client.println("<head><title>Login Failed</title></head>");
  client.println("<body><h1>Login Failed.</h1></body></html>");
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
    authentificated=false;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
       char c = client.read();
       //read char by char HTTP request
        linebuf[charcount]=c;
        if (charcount<sizeof(linebuf)-1) charcount++;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          if (authentificated)
            dashboardPage(client);
          else
            failedLoginPage(client);  
          break;
        }
        if (c == '\n') {
          if (strstr(linebuf,"GET /relay1off") > 0){
            digitalWrite(relay, HIGH);
            relay1State = "Off";
          }
          else if (strstr(linebuf,"GET /relay1on") > 0){
            digitalWrite(relay, LOW);
            relay1State = "On";
          }
          // you're starting a new line
          currentLineIsBlank = true;
          // checking if header is valid and contains the right username/password combination
          // dXNlcjpwYXNz = 'user:pass' (user:pass) base64 encode
          if (strstr(linebuf,"dXNlcjpwYXNz")>0 && strstr(linebuf,"Authorization: Basic")>0)
            authentificated=true;
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;          
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
