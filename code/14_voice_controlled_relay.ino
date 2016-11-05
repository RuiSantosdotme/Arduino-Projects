/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */
 
int relay = 11;     // pin Digital 11 
int state;          // saves the state
int flag=0;         // makes sure that the serial only prints once the state

void setup() {
    // sets the Relay as output:
    pinMode(relay, OUTPUT);
    digitalWrite(relay, HIGH); 
    
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}

void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
    // if the state is '0' the relay will turn OFF
    if (state == '0') {
        digitalWrite(relay, HIGH); 
        if(flag == 0){
          Serial.println("Relay Off!");
          flag=1;
        }
    }
    
    // if the state is '1' the relay will turn ON
    else if (state == '1') {
        digitalWrite(relay, LOW); 
        if(flag == 0){
          Serial.println("Relay On!");
          flag=1;
        }
    }
    //Uncomment For debugging purpose
    //Serial.println(state);
}
