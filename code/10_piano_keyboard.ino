/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

int button_midC = 2;
int button_Csharp = 3;
int button_D = 4;
int button_Dsharp = 5;
int button_E = 6;
int button_F = 7;
int button_Fsharp = 8;
int button_G = 9;
int button_Gsharp = 10;
int button_A = 11;

int speaker = 12;

int buttonstate_midC = 0;
int buttonstate_Csharp = 0;
int buttonstate_D = 0;
int buttonstate_Dsharp = 0;
int buttonstate_E = 0;
int buttonstate_F = 0;
int buttonstate_Fsharp = 0;
int buttonstate_G = 0;
int buttonstate_Gsharp = 0;
int buttonstate_A = 0;

//NOTES         midC  C#   D    D#   E    F    F#   G    G#   A
int tones[] = { 261, 277, 294, 311, 330, 349, 370, 392, 415, 440 }; //freq
int playedNote = 0;

void setup(){
  pinMode(button_midC, INPUT);
  pinMode(button_Csharp, INPUT);
  pinMode(button_D, INPUT);
  pinMode(button_Dsharp, INPUT);
  pinMode(button_E, INPUT);
  pinMode(button_F, INPUT);
  pinMode(button_Fsharp, INPUT);
  pinMode(button_G, INPUT);
  pinMode(button_Gsharp, INPUT);
  pinMode(button_A, INPUT);
  pinMode(speaker, OUTPUT);
}

void loop(){
  buttonstate_midC = digitalRead(button_midC);
  buttonstate_Csharp = digitalRead(button_Csharp);
  buttonstate_D = digitalRead(button_Dsharp);
  buttonstate_Dsharp = digitalRead(button_D);
  buttonstate_E = digitalRead(button_E);
  buttonstate_F = digitalRead(button_F);
  buttonstate_Fsharp = digitalRead(button_Fsharp);
  buttonstate_G = digitalRead(button_G);
  buttonstate_Gsharp = digitalRead(button_Gsharp);
  buttonstate_A = digitalRead(button_A);
  
  if(( buttonstate_midC == HIGH) || (buttonstate_Csharp == HIGH) || 
    (buttonstate_Dsharp == HIGH) || (buttonstate_D == HIGH) || 
    (buttonstate_E == HIGH) || (buttonstate_F == HIGH) || 
    (buttonstate_Fsharp == HIGH) || (buttonstate_G == HIGH)||
    (buttonstate_Gsharp ==HIGH) || (buttonstate_A ==HIGH)) { 
    if (buttonstate_midC == HIGH){
      playedNote = tones[0];
    } 
    if (buttonstate_Csharp == HIGH){
      playedNote = tones[1];
    }
    if (buttonstate_Dsharp == HIGH){
      playedNote = tones[2];
    }
    if (buttonstate_D == HIGH){
      playedNote = tones[3];
    }
    if (buttonstate_E == HIGH){
      playedNote = tones[4];
    }
    if (buttonstate_F == HIGH){
      playedNote = tones[5];
    }
    if (buttonstate_Fsharp == HIGH){
      playedNote = tones[6];
    }
    if (buttonstate_G == HIGH){
      playedNote = tones[7];
    }
    if (buttonstate_Gsharp == HIGH){
      playedNote = tones[8];
    }
    if (buttonstate_A == HIGH){
      playedNote = tones[9];
    }
    digitalWrite(speaker, HIGH);
    delayMicroseconds(playedNote);
    digitalWrite(speaker, LOW);
    delayMicroseconds(playedNote);
  }
  //in case no button is pressed, the buzzer doesn't beep
  else {
    digitalWrite(speaker, LOW);
  }
}
