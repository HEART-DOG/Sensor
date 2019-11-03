#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <SoftwareSerial.h>
#include <SPI.h>
#include <RF24.h>


//  Variables
//RF24 object with two pins defined with arguments. CE: 9, CSN: 10
RF24 radio(9, 10);
SoftwareSerial BTSerial(6,5);
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

const int heartSensor = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
long long address = 0x1234ABCDEFLL;
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
//char udsn[2] = {0};//USN, DSN저장 위한 케릭터배열 변수
String udsn="";
String msg = "";                               
struct msgdat{
  char msg[16];
  
}msgdata;
void setup() {   

  Serial.begin(9600);          // For Serial Monitor
  BTSerial.begin(9600);
  radio.begin();
 
  radio.openWritingPipe(address);
    //RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
    //NRF24L01: -18dBm, -12dBm,-6dBM, and 0dBm
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
 
  
  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(heartSensor);   
  pulseSensor.setThreshold(Threshold);   
  pulseSensor.begin();
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
//   if (pulseSensor.begin()) {
//    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
//  }
}


void loop() {

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
  if(BTSerial.available()){
//    BTSerial.readBytes(udsn, sizeof(udsn));
   udsn = BTSerial.readString();
  }                                               
//  msgdata.msg = String(myBPM) + ",";
  
  sprintf(msgdata.msg, "%d,%d", myBPM,atoi(udsn.c_str()));
  msg = String(myBPM) + "," + udsn;
  
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
    BTSerial.print(msg);                        // Print the value inside of myBPM. 
    radio.write(&msgdata, sizeof(msgdata));
    Serial.println(msg);
  }
  delay(20);                    // considered best practice in a simple sketch.

}

  
