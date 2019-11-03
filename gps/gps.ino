#include <SoftwareSerial.h>
 
SoftwareSerial GPS(2,3);
 
void setup() { 
  Serial.begin(9600);
  GPS.begin(9600);
}
 
void loop() {
  if(Serial.available()){
    GPS.write(Serial.read());
  }
  if(GPS.available()){
    Serial.write(GPS.read());
  }
}

//#include <SoftwareSerial.h>
// 
////SoftwareSerial GPS(3,2);
// 
//void setup() { 
//  Serial.begin(9600);
//  GPS.begin(9600);
//}
// 
//void loop() {
//  if(Serial.available()){
//    GPS.write(Serial.read());
//  }
//  if(GPS.available()){
//    Serial.write(GPS.read());
//  }
//}
