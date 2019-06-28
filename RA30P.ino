int SensorPin = A0;   //analog pin 0
int SensorPin1 = A1;  //analog pin 1
int SensorPin2 = A2;  //analog pin 2
int SensorPin3 = A3;  //analog pin 3
int SensorPin4 = A4;  //analog pin 4

int previous = 0; 
int const threshold = 10;       //subject to change

void setup(){
  Serial.begin(9600);
}
 
void loop(){
  int SensorReading = analogRead(SensorPin);          //Read pin 0
  int SensorReading1 = analogRead(SensorPin1);        //Read pin 1
  int SensorReading2 = analogRead(SensorPin2);        //Read pin 2
  int SensorReading3 = analogRead(SensorPin3);        //Read pin 3
  int SensorReading4 = analogRead(SensorPin4);        //Read pin 4
  
  int mfsr_r18 = map(SensorReading, 0, 1024);         //Mapping force values between 0 and 1024
  int asdf = map(SensorReading1, 0, 1024);            

  if (sensorReading > 10) {   //keep
    
  }

  if (sensorReading1 > 10) {
    //keep
  }

  if (sensorReading2 > 10) {
    //keep
  }

  if (sensorReading3 > 10) {
    //keep
  }

  if (sensorReading4 > 10) {
    //keep
  }

//  if (mfsr_r18 != 0) {
//    //Serial.println("Fist sensor being hit");
//    Serial.println(mfsr_r18);
//  }
  
  int difference = asdf - previous;
//  if (difference > 20) {
//    //Serial.println("Seond sensor being hit");
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
