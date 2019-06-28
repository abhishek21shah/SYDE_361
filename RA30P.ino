int SensorPin1 = A1;   //analog pin 1
int SensorPin2 = A2;  //analog pin 2
int SensorPin3 = A3;  //analog pin 3
int SensorPin4 = A4;  //analog pin 4
int SensorPin5 = A5;  //analog pin 5

int previous = 0; 
int const threshold = 10;       //subject to change

void setup(){
  Serial.begin(9600);
}
 
void loop(){
  int SensorReading1 = analogRead(SensorPin1);        //Read pin 1
  int SensorReading2 = analogRead(SensorPin2);        //Read pin 2
  int SensorReading3 = analogRead(SensorPin3);        //Read pin 3
  int SensorReading4 = analogRead(SensorPin4);        //Read pin 4
  int SensorReading5 = analogRead(SensorPin5);        //Read pin 5
  
  int mfsr_r18 = map(SensorReading, 0, 1024);         //Mapping force values between 0 and 1024
  int asdf = map(SensorReading1, 0, 1024);            

  if (sensorReading > threshold) {   //keep
    
  }

  if (sensorReading1 > threshold) {
    //keep
  }

  if (sensorReading2 > threshold) {
    //keep
  }

  if (sensorReading3 > threshold) {
    //keep
  }

  if (sensorReading4 > threshold) {
    //keep
  }

//  if (mfsr_r18 != 0) {
//    //Serial.println("Fist sensor being hit");
//    Serial.println(mfsr_r18);
//  }
  
  int difference = asdf - previous;
//  if (difference > 20) {
//    //Serial.println("Second sensor being hit");
//    //Serial.println(asdf);
//    
//  }
//  else {
//    Serial.println("No pin being hit");
//  }
  Serial.print(abs(difference));
  Serial.print(",");
  Serial.print(asdf);
  Serial.print(",");
  Serial.println(previous);
  previous = asdf;
  delay(100); 
}
