#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>



struct msgdat{
  char msg[16];
  
}msgdata;
char temp[100];


msgdat data;
void setup() {
  // RX, TX Serial SETUP
//  Wire.begin(8);
  Serial.begin(9600);                                  //Serial connection 
  Serial.print("start");
  // ---- WiFi Serial SETUP ----

  WiFi.begin("ddingg", "jmg12345");   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection");

  }

}
//void i2c_communication() {
//  Wire.requestFrom(8, sizeof(msgdata)); // 1 바이트 크기의 데이터 요청
//  if(Wire.available()){
//    Serial.write(Wire.read());
//  }
//  
//  Serial.println(data.msg); // 수신 데이터 출력
//}

void loop() {
  
//  while(Serial.available() == 0);
  byte leng = Serial.readBytes(temp, 20);
  for(int i = 0; i < leng; i++){
      Serial.print(temp[i]);
//      Serial.print("1");
    }
//  Serial.println(data);
    
//   i2c_communication();
//  if(recSerial.available()){
//    Serial.write(recSerial.read());
//  }
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;    //Declare object of class HTTPClient

    http.begin("http://caerang2.esllee.com/dog/select/process");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header

    String str = "";
    StaticJsonDocument<200> doc;
    JsonObject root = doc.to<JsonObject>();
    root["usn"] = 45;
    serializeJson(doc, str);
    int httpCode = http.POST(str);   //Send the request
    String payload = http.getString();                  //Get the response payload

    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload

    http.end();  //Close connection

  } else {

    Serial.println("Error in WiFi connection");

  }

  delay(3000);  //Send a request every 30 seconds

}
