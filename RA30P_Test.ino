#include <Wire.h> 

#define SensorPin1 A1 
#define SensorPin2 A2
#define SensorPin3 A3 
#define SensorPin4 A4
#define SensorPin5 A5 

const int threshold = 30;  //subject to change
int channel = 9;  // Defines the MIDI channel to send messages on

elapsedMillis timer = 0;

int notes[] = {61,61,60,61,61};
int prev_state[] = {0,0,0,0,0}; 
int new_state[] = {0,0,0,0,0}; 

//int prev_1 = 0;
//int prev_2 = 0;
//int prev_3 = 0;
//int prev_4 = 0;
//int prev_5 = 0;
//
//int new_1 = 0;
//int new_2 = 0;
//int new_3 = 0;
//int new_4 = 0;
//int new_5 = 0;



void setup(){
  Serial.begin(9600);
}
 
void loop(){
  getCurrentState();

  if(timer > 110){
    
    // Check Pot
    check_drums();

    timer = 0;

     for (int i = 0; i < 5; i++){
    prev_state[i] = new_state[i];
   }
  }
  
  // Update our state
  //memcpy(new_state,prev_state, sizeof(prev_state));

// for (int i = 0; i < 5; i++){
//  prev_state[i] = new_state[i];
// }
    //prev_1 = new_1;
    //new_1 = prev_1;
    //Serial.println(new_1);
}

void getCurrentState() {
  new_state[0] = analogRead(SensorPin1) >= threshold ? analogRead(SensorPin1) : 0;        //Read pin 1
  new_state[1] = analogRead(SensorPin2) >= threshold ? analogRead(SensorPin2) : 0;        //Read pin 2
  new_state[2] = analogRead(SensorPin3) >= threshold ? analogRead(SensorPin3) : 0;        //Read pin 3
  new_state[3] = analogRead(SensorPin4) >= threshold ? analogRead(SensorPin4) : 0;        //Read pin 4
  new_state[4] = analogRead(SensorPin5) >= threshold ? analogRead(SensorPin5) : 0;        //Read pin 5

// new_1 = analogRead(SensorPin1) >= threshold ? analogRead(SensorPin1) : 0;  
// new_2 = analogRead(SensorPin2) >= threshold ? analogRead(SensorPin2) : 0;  
// new_3 = analogRead(SensorPin3) >= threshold ? analogRead(SensorPin3) : 0;  
// new_4 = analogRead(SensorPin4) >= threshold ? analogRead(SensorPin4) : 0;  
// new_5 = analogRead(SensorPin5) >= threshold ? analogRead(SensorPin5) : 0;  

  Serial.print(new_state[0]); 
  Serial.print(", "); 
  Serial.print(new_state[1]); 
  Serial.print(", "); 
  Serial.print(new_state[2]); 
  Serial.print(", "); 
  Serial.print(new_state[3]); 
  Serial.print(", "); 
  Serial.print(new_state[4]); 
  Serial.print('\n'); 

//    Serial.print("new: "); 
//    Serial.println(new_state[0]);
//    Serial.print("prev: "); 
//    Serial.println(prev_state[0]);
  
}

void check_drums(){
  for(int n = 0; n < 5; n++){
//     Serial.print("new: "); 
//     Serial.println(new_state[n]);
//     Serial.print("old: "); 
//     Serial.println(prev_state[n]);
     if((new_state[n] - prev_state[n] > 30) && (new_state[n] > 0)) {
       int vel = map(new_state[n], 0, 1023, 0, 127); 
       usbMIDI.sendNoteOn(notes[n], vel, channel);
//       Serial.print("new: "); 
//       Serial.println(new_state[n]);
//       Serial.print("old: "); 
//       Serial.println(prev_state[n]);
     } else { 
       usbMIDI.sendNoteOff(notes[n], 0, channel); 
     }   
  }
}
