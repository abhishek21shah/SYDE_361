#include <Wire.h> 
#include <stdio.h>

#define SensorPin1 A1 
#define SensorPin2 A2
#define SensorPin3 A3 
#define SensorPin4 A4
#define SensorPin5 A5
#define SensorPin6 A6
#define SensorPin7 A7
#define SensorPin8 A8
#define SensorPin9 A9

// Will need to define the other SensorPins
// Need to change the max method???

const int threshold = 30;  //subject to change
int channel = 9;  // Defines the MIDI channel to send messages on

elapsedMillis timer = 0;

//int notes[] = {63,63,60,63,63};
int note;
int prev_state[] = {0,0,0,0,0,0,0,0,0}; 
int new_state[] = {0,0,0,0,0,0,0,0,0};

int max1;
int max2;
const double r = 11.0;  // Radius from middle of senor 3 to outer sensors
const double arc = 17.2787; // One fourth arc distance between the outer sensors

void setup(){
  Serial.begin(9600);
}
 
void loop(){
  getCurrentState();

  if(timer > 220){
    
    // Check Pot
    check_drums();

    timer = 0;

     for (int i = 0; i < 9; i++){
    prev_state[i] = new_state[i];
   }
  }
}

void BiLinear(int a, int b, int c, int d, int e) {
  
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

  double bb = (max1*arc) / (max1 + max2);
  double f_avg = (arc*max1 - bb*max1 + bb*max2) / arc;
  double cc = (r*f_avg) / (f_avg + new_state[2]);

//  if (max1 != 0 && max2 != 0 && bb != 0 && f_avg != 0)
//  {
//    Serial.print(max1);
//    Serial.print(", ");
//    Serial.print(max2);
//    Serial.print(", ");
//    Serial.print(bb);
//    Serial.print(", ");
//    Serial.print(f_avg);
//    Serial.print(", ");
//    Serial.print(cc);
//    Serial.println();
//  }

//  if (a != 0 && b == 0 && e == 0 && c == 0 && d == 0) {
//      cc = 11.0;
//    }
//    else if (a == 0 && b != 0 && e == 0 && c == 0 && d == 0) {
//      cc = 11.0;
//    }
//    else if (a == 0 && b == 0 && e == 0 && c != 0 && d == 0) {
//      cc = 11.0;
//    }
//    else if (a == 0 && b == 0 && e == 0 && c == 0 && d != 0) {
//      cc = 11.0;
//    }
//    else if (a == 0 && b == 0 && e != 0 && c == 0 && d == 0) {
//      cc = 0.0;
//    }
//
//    if (a != 0 && b == 0 && e != 0 && c == 0 && d == 0) {
//      cc = r*max1 / (max1 + e); 
//    }
//    else if (a == 0 && b != 0 && e != 0 && c == 0 && d == 0) {
//      cc = r*max1 / (max1 + e); 
//    }
//    else if (a == 0 && b == 0 && e != 0 && c != 0 && d == 0) {
//      cc = r*max1 / (max1 + e); 
//    }
//    else if (a == 0 && b == 0 && e != 0 && c == 0 && d != 0) {
//      cc = r*max1 / (max1 + e); 
//    }

//    if (cc <= 4.0)
//    {
//      //play zone 1 sound
//      note = 60;
//      Serial.println("Zone 1 Sound");
//    }
//    else if ( cc >= 4.01 && cc <= 7.0)
//    {
//      //play zone 2 sound
//      note = 90;
//      Serial.println("Zone 2 Sound");
//    }
//    else if ( cc >= 7.01)
//    {
//      //play zone 3 sound
//      note = 120;
//      Serial.println("Zone 3 Sound");
//    }
//    else {
//      Serial.println("No sound");
//    }
//    
//  Serial.println(cc);
}

void getCurrentState() {
  new_state[0] = analogRead(SensorPin1) >= threshold ? analogRead(SensorPin1) : 0;        //Read pin 1
  new_state[1] = analogRead(SensorPin2) >= threshold ? analogRead(SensorPin2) : 0;        //Read pin 2
  new_state[2] = analogRead(SensorPin3) >= threshold ? analogRead(SensorPin3) : 0;        //Read pin 3
  new_state[3] = analogRead(SensorPin4) >= threshold ? analogRead(SensorPin4) : 0;        //Read pin 4
  new_state[4] = analogRead(SensorPin5) >= threshold ? analogRead(SensorPin5) : 0;        //Read pin 5
  new_state[5] = analogRead(SensorPin6) >= threshold ? analogRead(SensorPin6) : 0;        //Read pin 6
  new_state[6] = analogRead(SensorPin7) >= threshold ? analogRead(SensorPin7) : 0;        //Read pin 7
  new_state[7] = analogRead(SensorPin8) >= threshold ? analogRead(SensorPin8) : 0;        //Read pin 8
  new_state[8] = analogRead(SensorPin9) >= threshold ? analogRead(SensorPin9) : 0;        //Read pin 9

  Serial.print(new_state[0]); 
  Serial.print(", "); 
  Serial.print(new_state[1]); 
  Serial.print(", "); 
  Serial.print(new_state[2]); 
  Serial.print(", "); 
  Serial.print(new_state[3]); 
  Serial.print(", "); 
  Serial.print(new_state[4]);
  Serial.print(", "); 
  Serial.print(new_state[5]);
  Serial.print(", "); 
  Serial.print(new_state[6]);
  Serial.print(", "); 
  Serial.print(new_state[7]);
  Serial.print(", "); 
  Serial.print(new_state[8]);
  Serial.print('\n');
  
  if (new_state[0] > threshold || new_state[1] > threshold || new_state[2] > threshold || new_state[3] > threshold)
  {
    note = 38;
    //Serial.println("Zone 3");
  }
  
 if (new_state[4] > threshold || new_state[5] > threshold || new_state[6] > threshold || new_state[7] > threshold)
  {
    note = 40;
    //Serial.println("Zone 2");
  }
  
  if (new_state[8] > threshold)
  {
    note = 42;
    //Serial.println("Zone 1");
  }
  //BiLinear(new_state[0], new_state[1], new_state[3], new_state[4], new_state[2]);
    
}

void check_drums(){
  for(int n = 0; n < 9; n++){
     if((new_state[n] - prev_state[n] > threshold) && (new_state[n] > 0)) {
       int vel = map(new_state[n], 0, 1023, 0, 127); 
       usbMIDI.sendNoteOn(note, vel, channel);
     } else { 
       usbMIDI.sendNoteOff(note, 0, channel); 
     }   
  }
}
