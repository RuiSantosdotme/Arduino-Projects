/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

// Example testing sketch for various DHT humidity/temperature sensors
#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <RTClib.h>
#include <SFE_BMP180.h>

//define DHT pin
#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Data loggin SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 10; 

//creating a file to store the data
File myFile;

//For the RTC
RTC_DS1307 rtc;

//You need to create an SFE_BMP180 object, here called "pressure":
SFE_BMP180 pressure;

#define ALTITUDE 100 // Set here your altitude

void setup() {

  //initializing the DHT sensor
  dht.begin();

  //initializing Serial monitor
  Serial.begin(9600);
  
  // setup for the RTC
  while (!Serial); // for Leonardo/Micro/Zero
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if(pressure.begin())
    Serial.println("BMP180 init success");
  else {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever. 
  }
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile=SD.open("DATA.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    myFile.println("Date,Time,Temperature ºC,Humidity %,Pressura hPa");
  }
  myFile.close();
}

void loggingTime(){
  DateTime now = rtc.now();
  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(" ");
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(",");
  }
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.day(), DEC);
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  myFile.close();
  delay(1000);  
}

void loggingTemperature () {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  //float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) /*|| isnan(f)*/) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  //debugging purposes
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.println(" %");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C");
  //Serial.print(f);
  //Serial.println(" *F\t"); 
  
  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("open with success");
    myFile.print(t);
    myFile.print(",");
    myFile.print(h);
    myFile.print(",");
  }
  myFile.close();
}
void loggingPressure(){
  char status;
  double T,P,a;
  status = pressure.startTemperature();
  if (status != 0){
    // Wait for the measurement to complete:
    delay(status);
    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.
    status = pressure.getTemperature(T);
    if (status != 0){
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0){
        // Wait for the measurement to complete:
        delay(status);

        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0){
          myFile = SD.open("DATA.txt", FILE_WRITE);
          if (myFile) {
            myFile.println(P,2);
            Serial.println("Pressure is ok");
          }
          myFile.close();
        }
        else Serial.println("error retrieving pressure measurement\n"); //for debugging
      }
      else Serial.println("error starting pressure measurement\n"); //for debugging
    }
    else Serial.println("error retrieving temperature measurement\n"); //for debugging
  }
  else Serial.println("error starting temperature measurement\n"); //for debugging
  
}

void loop() {
  loggingTime();
  loggingTemperature();
  loggingPressure();
  delay(5000);
}
