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
#define threshold 30      // Threshold to compare force values against
#define channel 9         // Defines the MIDI channel to send messages on

elapsedMillis timer = 0;

int note;

int number_of_sensors_triggered_Z1 = 0;
int number_of_sensors_triggered_Z2 = 0;
int number_of_sensors_triggered_Z3 = 0;

int zone2[] = {0,0,0,0};
int zone3[] = {0,0,0,0};

int prev_state[] = {0,0,0,0,0,0,0,0,0};
int new_state[] = {0,0,0,0,0,0,0,0,0};

void setup()
{
  Serial.begin(9600);
}
 
void loop(){
  getCurrentState();

  if(timer > 220)
  {
    determineLocation();        // Check to see which zone(s) is/are being triggered

    check_drums();              // Check Pot

    timer = 0;

     for (int i = 0; i < 9; i++)
     {
      prev_state[i] = new_state[i];
     }
  }
}

void determineLocation() 
{
  for (int x = 0; x < 4; x++) 
  {
    zone2[x] = new_state[x+3] - prev_state[x+3];
    zone3[x] = new_state[x] - prev_state[x];
  }

  for (int i = 0; i < 4; i++) 
  {
    if (zone2[i+3] > threshold) 
    { 
       number_of_sensors_triggered_Z2 += 1; 
    }
    
    if (zone3[i] > threshold) 
    { 
       number_of_sensors_triggered_Z3 += 1; 
    }
  } 

  if ((new_state[8] - prev_state[8]) > threshold) 
  { 
    number_of_sensors_triggered_Z1 = 1; 
  }
    
  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 > 0))         // All 3 zones are triggered
  {
    note = 39; 
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 == 0))        // Zones 1 & 3 are triggered
  { 
    note = 38; 
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 > 0))        // Zones 1 & 2 are triggered
  { 
    note = 40; 
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 == 0))       // ONLY Zone 2 is triggered
  { 
    note = 42; 
  }

  if ((number_of_sensors_triggered_Z2 == 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 == 0))       // ONLY Zone 3 is triggered
  {         
    note = 40;
  }

  if ((number_of_sensors_triggered_Z2 == 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 > 0))       // ONLY Zone 1 is triggered
  { 
    note = 38; 
  }

}

void getCurrentState() 
{
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
  Serial.println();
}

void check_drums()
{
  for (int n = 0; n < 9; n++)
  {
     if ((new_state[n] - prev_state[n] > threshold) && (new_state[n] > 0)) 
     {
       int vel = map(new_state[n], 0, 1023, 0, 127); 
       usbMIDI.sendNoteOn(note, vel, channel);
     } 
     else 
     { 
       usbMIDI.sendNoteOff(note, 0, channel); 
     }   
  }
}
