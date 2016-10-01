/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */
 
#include <Wire.h> //for I2C communication
#include <Adafruit_GFX.h> // include library for the OLED
#include <Adafruit_SSD1306.h> // include library for the OLED
#include <SFE_BMP180.h> // include library for the pressure sensor
#include <DHT.h> //include library for the temperature and humidity sensor

#define DHTPIN 2     // pin that DTH11 is connected
#define DHTTYPE DHT11   // DHT 11
#define OLED_RESET 4    //OLED
#define DS3231_I2C_ADDRESS 0x68
Adafruit_SSD1306 display(OLED_RESET);
#define ALTITUDE 100 // set with your altitude

SFE_BMP180 pressure;

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

// Convert normal decimal numbers to binary coded decimal (used to convert time)
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}

void setup(){
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else {
    // Oops, something went wrong, this is usually a connection problem,
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  Wire.begin();  // initialize wire communication
  dht.begin();  //initialize  dht sensor 
  Serial.begin(9600); // initialize  serial monitor
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize display
  
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // uncomment the following line after setting up the time once
  setDS3231time(33,21,11,5,29,9,16);
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year){
  //set the time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year){
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

// Displays data and time on the OLED display
void displayTime(){ 
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  display.clearDisplay(); //clearing the display
  display.setTextColor(WHITE); //setting the color to white
  display.setTextSize(1); //setting the color size
  display.setCursor(0,0); //set the cursor coordinates
  // dispaying the day of the week
  switch(dayOfWeek){ 
    case 1:
      display.print("Sunday");
      break;
    case 2:
      display.print("Monday");
      break;
    case 3:
      display.print("Tuesday");
      break;
    case 4:
      display.print("Wednesday");
      break;
    case 5:
      display.print("Thursday");
      break;
    case 6:
      display.print("Friday");
      break;
    case 7:
     display.print("Saturday");
      break;
  }
  display.setCursor(0,20); // setting the cursor coordinates
  display.print(hour, DEC); //display the hour
  // convert the byte variable to a decimal number when displayed
  
  display.print(":");
  if (minute<10){
    display.print("0");
  }
  display.print(minute, DEC);
  display.print(":");
  if (second<10){
    display.print("0");
  }
  display.print(second, DEC);
  display.setCursor(0,10);
  display.print(dayOfMonth, DEC);
  display.print("/");
  display.print(month, DEC);
  display.print("/");
  display.print(year, DEC);
}
// Displays the temperature and humidity
void displayTempHumid(){

  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setTextSize(1);
   display.setCursor(5,0);
   display.print("Failed to read from DHT sensor!");
   return;
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Humidity: "); 
  display.print(h);
  display.print(" %\t");
  
  // Comments this section and uncomment below if you prefer to display temperature in Fahrenheit
  display.setCursor(0,10);
  display.print("Temp: "); 
  display.print(t);
  display.print(" C"); 
  
  // Uncomment this part if you want to display the temperature in Fahrenheit
  /*display.setCursor(0,10);
  display.print("Temp: "); 
  display.print(t*1.8+32);
  display.print(" F"); */
}

// Displays pressure
void displayPressure(){ 
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
          // Print out the measurement:
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(0,20);
          display.print("Pressure: ");
          display.print(P,2);
          display.print(" mb ");
        }
        else Serial.println("error retrieving pressure measurement\n"); //for debugging
      }
      else Serial.println("error starting pressure measurement\n"); //for debugging
    }
    else Serial.println("error retrieving temperature measurement\n"); //for debugging
  }
  else Serial.println("error starting temperature measurement\n"); //for debugging
}
void loop(){
  displayTempHumid();
  displayPressure();
  display.display();
  delay(3000);
  displayTime(); 
  display.display();
  delay(3000);
}
