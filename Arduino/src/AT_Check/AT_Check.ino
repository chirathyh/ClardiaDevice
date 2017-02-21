#include <SoftwareSerial.h>

#define SSID "Dialog4G"
#define PASSWORD "8JBNRFRN4HA"
#define apiKey "L8EYC0LQQYWU62DW"

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  connectWiFi();
}

void loop() {
  updateThingSpeak();
}

boolean connectWiFi(){
  Serial1.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASSWORD;
  cmd+="\"";
  Serial1.println(cmd);
  delay(5000);
  Serial.println("connected");
}

void updateThingSpeak(){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149";
  cmd += "\",80";
  Serial1.println(cmd); //AT+CIPSTART="TCP","184.106.153.149",80
  if(Serial1.find("OK")){
    Serial.println("Connected to ThingSpeak");
       
    String getStr = "GET /update?api_key=";
    getStr += apiKey;
    getStr +="&field1=";
    getStr += String(10000);
    getStr += "\r\n\r\n";
  
    // send data length
    cmd = "AT+CIPSEND=";
    cmd += String(getStr.length());
    Serial1.println(cmd);
  
    if(Serial1.find(">")){
      Serial1.print(getStr);
      Serial.println("Data Sended");
    }
    else{
      Serial1.println("AT+CIPCLOSE");
      Serial.println("Data Failed");
    }
  }

}
