int SensorPin1 = A1;  //analog pin 1 - Edge of drum
int SensorPin2 = A2;  //analog pin 2 - Edge of drum
int SensorPin3 = A3;  //analog pin 3 - Centre of drum
int SensorPin4 = A4;  //analog pin 4 - Edge of drum
int SensorPin5 = A5;  //analog pin 5 - Edge of drum

int sensorVelocity1 = 0;
int sensorVelocity2 = 0;
int sensorVelocity3 = 0;
int sensorVelocity4 = 0;
int sensorVelocity5 = 0;

int const threshold = 10;  //subject to change
int channel = 1;  // Defines the MIDI channel to send messages on

void setup(){
  Serial.begin(9600);
}
 
void loop(){

  // Filter out the forces below the threshold by setting the reading to 0
  int sensorReading1 = analogRead(SensorPin1) >= threshold ? analogRead(SensorPin1) : 0;        //Read pin 1
  int sensorReading2 = analogRead(SensorPin2) >= threshold ? analogRead(SensorPin2) : 0;        //Read pin 2
  int sensorReading3 = analogRead(SensorPin3) >= threshold ? analogRead(SensorPin3) : 0;        //Read pin 3
  int sensorReading4 = analogRead(SensorPin4) >= threshold ? analogRead(SensorPin4) : 0;        //Read pin 4
  int sensorReading5 = analogRead(SensorPin5) >= threshold ? analogRead(SensorPin5) : 0;        //Read pin 5
  
  calculateVelocities(sensorReading1, sensorReading2, sensorReading3, sensorReading4, sensorReading5);
  sendNotes(sensorVelocity1, sensorVelocity2, sensorVelocity3, sensorVelocity4, sensorVelocity5);
}

void calculateVelocities(int sensorReading1, int sensorReading2, int sensorReading3, int sensorReading4, int sensorReading5) {
  // Calculate velocity for each sensor based on sensor reading - higher velocity -> louder, lower velocity -> quieter
  // Sensor readings range from 0-1023 and velocity values range from 0-127
  sensorVelocity1 = map(sensorReading1, 0, 1023, 0, 127);
  sensorVelocity2 = map(sensorReading2, 0, 1023, 0, 127);
  sensorVelocity3 = map(sensorReading3, 0, 1023, 0, 127);
  sensorVelocity4 = map(sensorReading4, 0, 1023, 0, 127);
  sensorVelocity5 = map(sensorReading5, 0, 1023, 0, 127);
}

void sendNotes(int sensorVelocity1, int sensorVelocity2, int sensorVelocity3, int sensorVelocity4, int sensorVelocity5) {
  // Send MIDI note based on sensor velocities
  // Sensor 3 is A4 (note 69), all other sensors are F4 (note 64) - subject to change
  // Send all notes from all sensors through MIDI - sequentially? 
  
  usbMIDI.sendNoteOn(69, sensorVelocity3, channel); // Turns note A4 on
  usbMIDI.sendNoteOn(64, sensorVelocity1, channel); // Turns note F4 on
  usbMIDI.sendNoteOn(64, sensorVelocity2, channel);
  usbMIDI.sendNoteOn(64, sensorVelocity4, channel);
  usbMIDI.sendNoteOn(64, sensorVelocity5, channel);
  
//  usbMIDI.sendNoteOff(69, velocity, channel);
}
