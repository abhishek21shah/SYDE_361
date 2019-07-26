#include <Wire.h> 
#include <stdio.h>

#define SensorPin1 A3       
#define SensorPin2 A8
#define SensorPin3 A7
#define SensorPin4 A1
#define SensorPin5 A4
#define SensorPin6 A9
#define SensorPin7 A6
#define SensorPin8 A2
#define SensorPin9 A5

const int threshold = 30;                         // Force value to compare against
int channel = 9;                                  // Defines the MIDI channel to send messages on

elapsedMillis timer = 0;                          // Millis timer

int note;                                         // Impact force values to send via MIDI channel

int prev_state[] = {0,0,0,0,0,0,0,0,0};           // Previous state Force value readings for all pin sensors (9)
int new_state[] = {0,0,0,0,0,0,0,0,0};            // New state Force value readings for all pin sensors (9)

void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
  getCurrentState();                              // Determine location of the impact zone(s) and capture the force value readings

  if(timer > 200){

    //determineLocation(); 
    // Check Pot
    check_drums();

    timer = 0;                                    // Reset timer to 0

     for (int i = 0; i < 9; i++)                  // Copy previous state force values to new state
     {
      prev_state[i] = new_state[i];
     }
  }
}                                                 // End Loop
you 
void determineLocation() 
{
  int number_of_sensors_triggered_Z1 = 0;                     // Track the number of sensors triggered in zone 1  
  int number_of_sensors_triggered_Z2 = 0;                     // Track the number of sensors triggered in zone 2
  int number_of_sensors_triggered_Z3 = 0;                     // Track the number of sensors triggered in zone 3

  int zone2[] = {0,0,0,0};                                    // Array to track the 4 sensors in zone 2
  int zone3[] = {0,0,0,0};                                    // Array to track the 4 sensors in zone 3
  
  for (int x = 0; x < 4; x++) 
  {
    zone2[x] = new_state[x+4] - prev_state[x+4];
    zone3[x] = new_state[x] - prev_state[x];
  }
  
  for (int i = 0; i < 4; i++) 
  {
    if (zone2[i] > threshold)                                 // Only trigger sensor values that are greater than the threshold
    { 
       number_of_sensors_triggered_Z2+=1; 
    }
    
    if (zone3[i] > threshold)                                 // Only trigger sensor values that are greater than the threshold
    { 
       number_of_sensors_triggered_Z3+=1; 
    }
  } 
  
  if ((new_state[8] - prev_state[8]) > threshold )            // Zone 1 consists of only one sensor, so toggle between 0 and 1 if force value is greater than threshold
  { 
    number_of_sensors_triggered_Z1 = 1; 
  }
<<<<<<< HEAD

  if ((number_of_sensors_triggered_Z2 == 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 > 0)) { // ONLY z1 is triggered
    note = 38; // F2#
    Serial.println("z1");
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 > 0)) { // z2 and z1 are triggered
    note = 39; // F2
    Serial.println("z1 and z2");
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 == 0)) { // ONLY z2 is triggered
    note = 40; // E2
    Serial.println("z2");
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 == 0)) { // z2 and z3 are triggered
    note = 41; // D2 sharp
    Serial.println("z2 and z3");
  }

  if ((number_of_sensors_triggered_Z2 == 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 == 0)) { // ONLY z3 is triggered
    note = 42; // D2
    Serial.println("z3");
  }
    
  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 > 0)) { // All 3 are triggered
    note = 43; // G2
    Serial.println("all 3");
=======
    
  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 > 0))       // All 3 are triggered
  {     
    note = 43;
    Serial.println("all 3");
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 == 0))      // z2 and z3 are triggered
  { 
    note = 39;
    Serial.println("z2 and z3");
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 > 0))      // z2 and z1 are triggered
  {
    note = 41;
    Serial.println("z1 and z2");
  }

  if ((number_of_sensors_triggered_Z2 > 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 == 0))     // ONLY z2 is triggered
  { 
    note = 40;
    Serial.println("z2");
  }

  if ((number_of_sensors_triggered_Z2 == 0) && (number_of_sensors_triggered_Z3 > 0) && (number_of_sensors_triggered_Z1 == 0))     // ONLY z3 is triggered
  { 
    note = 38;
    Serial.println("z3");
  }

  if ((number_of_sensors_triggered_Z2 == 0) && (number_of_sensors_triggered_Z3 == 0) && (number_of_sensors_triggered_Z1 > 0))     // ONLY z1 is triggered
  { 
    note = 42;
    Serial.println("z1");
>>>>>>> bec3c3f72fa353a74de2ae8a09d7e1c5aa57bd09
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

  determineLocation();                                                                    //function call to determine which zones are being triggered

  //Print force values onto serial monitor
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
}

void check_drums()
{
  for(int n = 0; n < 9; n++)
  {
     if((new_state[n] - prev_state[n] > threshold) && (new_state[n] > 0)) 
     {
       int vel = map(new_state[n], 0, 1023, 0, 127);                                  
       usbMIDI.sendNoteOn(note, vel, channel);                                            //MIDI Channel = 9, note = force value, vel
     } else { 
       usbMIDI.sendNoteOff(note, 0, channel); 
     }   
  }
}
