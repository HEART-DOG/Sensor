//Libraries for NRF24L01+ module.
#include <SPI.h>
#include <Wire.h>
#include <RF24.h>
#include <SoftwareSerial.h>

SoftwareSerial sendSerial(5,4); // rx, tx


//RF24 object with two pins defined with arguments. CE: 9, CSN: 10
RF24 radio(9, 10);
struct msgdat{
  byte msg[16];
  
}msgdata;

//Address of the pipe. 40 bit long, you can choose this freely.
//Remember to use different address in different projects.
long long address = 0x1234ABCDEFLL;
//String msg = "123,";
void setup() {
  //Start the radio
  Serial.begin(9600);
  sendSerial.begin(9600);
  radio.begin();
//  Wire.begin();
 
  radio.openReadingPipe(1, address);
  radio.startListening();
}
 
void loop() {
//  Wire.beginTransmission(8);
  Serial.write('12346');
  if(radio.available()) {
      sendSerial.println("TEST");

      //While the data is available...
      while (radio.available()) {
        //Update temperature -variable with data from the radio module
        radio.read(&msgdata, sizeof(msgdata));
      }
      
//      sendSerial.println(msgdata.msg);  
//      Serial.write(msgdata.msg);
        Serial.write("b");
//      Wire.write(msgdata.msg);
//      Wire.endTransmission();
    }
}
