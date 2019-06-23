int SensorPin = A0; //analog pin 0
int SensorPin1 = A1;
int previous = 0; 

void setup(){
  Serial.begin(9600);
}
 
void loop(){
  int SensorReading = analogRead(SensorPin); 
  int SensorReading1 = analogRead(SensorPin1);
  
  int mfsr_r18 = map(SensorReading, 0, 1024, 0, 255);
  int asdf = map(SensorReading1, 0, 1024, 0, 255);

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
