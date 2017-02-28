/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */
 
int led = 11;     // pin Digital 11 
int state;          // saves the state
int flag = 0;         // makes sure that the serial only prints once the state

void setup() {
    // sets the Relay as output:
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW); 
    
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}

void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
    // if the state is '0' the LED will turn OFF
    if (state == '0') {
        digitalWrite(led, LOW); 
        if(flag == 0){
          Serial.println("LED Off!");
          flag=1;
        }
    }
    
    // if the state is '1' the LED will turn ON
    else if (state == '1') {
        digitalWrite(led, HIGH); 
        if(flag == 0){
          Serial.println("LED On!");
          flag=1;
        }
    }
    //Uncomment For debugging purpose
    //Serial.println(state);
}
