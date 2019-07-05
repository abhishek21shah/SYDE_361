#include <Wire.h> 
#include <stdio.h>

#define SensorPin1 A1 
#define SensorPin2 A2
#define SensorPin3 A3 
#define SensorPin4 A4
#define SensorPin5 A5 

const int threshold = 30;  //subject to change
int channel = 9;  // Defines the MIDI channel to send messages on

elapsedMillis timer = 0;

int notes[] = {63,63,60,63,63};
int prev_state[] = {0,0,0,0,0}; 
int new_state[] = {0,0,0,0,0};

int max1;
int max2;
int r = 11;  // Radius from middle of senor 3 to outer sensors
int arc = 17.2787; // One fourth arc distance between the outer sensors

void setup(){
  Serial.begin(9600);
}
 
void loop(){
  getCurrentState();

  if(timer > 180){
    
    // Check Pot
    check_drums();

    timer = 0;

     for (int i = 0; i < 5; i++){
    prev_state[i] = new_state[i];
   }
  }
}


void BiLinear(int a, int b, int c, int d) {
  
  max1 = max(max(a,b), max(c,d));

  if (max(a,b) < max(c,d)) 
  {
    if (max(a,b) > c || max(a,b) > d) 
    {
      max2 = max(a,b);
    }  
     else if (c > d)
     {
       max2 = d;
     }
     else 
     {
      max2 = c;
     }  
  }
  else 
  {
    if (max(c,d) > a || max(c,d) > b) 
    {
      max2 = max(c,d);
    } 
     else if (a > b) 
     {
      max2 = b;
     }
     
     else 
     {
      max2 = a;
     }
   }

  Serial.print(max1);
  Serial.print(", ");
  Serial.print(max2);
  Serial.print('\n');
 
}

void getCurrentState() {
  new_state[0] = analogRead(SensorPin1) >= threshold ? analogRead(SensorPin1) : 0;        //Read pin 1
  new_state[1] = analogRead(SensorPin2) >= threshold ? analogRead(SensorPin2) : 0;        //Read pin 2
  new_state[2] = analogRead(SensorPin3) >= threshold ? analogRead(SensorPin3) : 0;        //Read pin 3
  new_state[3] = analogRead(SensorPin4) >= threshold ? analogRead(SensorPin4) : 0;        //Read pin 4
  new_state[4] = analogRead(SensorPin5) >= threshold ? analogRead(SensorPin5) : 0;        //Read pin 5

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
  BiLinear(new_state[0], new_state[1], new_state[3], new_state[4]);  
}

void check_drums(){
  for(int n = 0; n < 5; n++){
     if((new_state[n] - prev_state[n] > 30) && (new_state[n] > 0)) {
       int vel = map(new_state[n], 0, 1023, 0, 127); 
       usbMIDI.sendNoteOn(notes[n], vel, channel);
     } else { 
       usbMIDI.sendNoteOff(notes[n], 0, channel); 
     }   
  }
}
