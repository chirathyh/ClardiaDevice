/**
 * @example TCPServer.ino
 * @brief The TCPServer demo of library WeeESP8266. 
 * @author Wu Pengfei<pengfei.wu@itead.cc> 
 * @date 2015.02
 * 
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "ESP8266.h"
#include "Protocentral_MAX30100.h"
#include <Wire.h>

#define SSID        "Dialog 4G"
#define PASSWORD    "8JBNRFRN4HA"
#define BUZZER A1

ESP8266 wifi(Serial1,115200);

MAX30100 sensor;
uint8_t data_len=8;
uint8_t DataPacketHeader[15];
volatile  long IRR,REDD;

volatile long red [300];
volatile long ir [300];
int i=0;

void setup(void)
{

  
    pinMode(BUZZER, OUTPUT);
    Serial.begin(9600);
    Serial.print("setup begin\r\n");

    Wire.begin();
    while(!Serial);
    sensor.begin(pw1600, i50, sr100 );
    sensor.printRegisters();
    
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
      
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }
 
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");
        Serial.println(wifi.getLocalIP().c_str());    
    } else {
        Serial.print("Join AP failure\r\n");
        buzzer(1500);
    }
    
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    }

    
    if (wifi.startTCPServer(8090)) {
        Serial.print("start tcp server ok\r\n");
    } else {
        Serial.print("start tcp server err\r\n");
        buzzer(1500);
    }
    
    if (wifi.setTCPServerTimeout(10)) { 
        Serial.print("set tcp server timout 10 seconds\r\n");
    } else {
        Serial.print("set tcp server timout err\r\n");
        buzzer(1500);
    }
    
    Serial.print("setup end\r\n");
    buzzer(500);
}



void loop(void)
{
/*
     Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        //delay(100);
        */
    uint8_t buffer[128] = {0};
    uint8_t mux_id;
    
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        Serial.print("Received from :");
        Serial.print(mux_id);
        Serial.print("[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
        buzzer(100);

        //uint32_t x[300] = {10001,10002,10003,10004,10005,10006,10007,10008,10009,10010,10011,10012,10013,10014,10015,10016,10017,10018,10019,10020,10021,10022,10023,10024,10025,10026,10027,10028,10029,10030,20001,20002,20003,20004,20005,20006,20007,20008,20009,20010,20011,20012,20013,20014,20015,20016,20017,20018,20019,20020,20021,20022,20023,20024,20025,20026,20027,20028,20029,20030,30001,30002,30003,30004,30005,30006,30007,30008,30009,30010,30011,30012,30013,30014,30015,30016,30017,30018,30019,30020,30021,30022,30023,30024,30025,30026,30027,30028,30029,30030,40001,40002,40003,40004,40005,40006,40007,40008,40009,50000,10001,10002,10003,10004,10005,10006,10007,10008,10009,10010,10011,10012,10013,10014,10015,10016,10017,10018,10019,10020,10021,10022,10023,10024,10025,10026,10027,10028,10029,10030,20001,20002,20003,20004,20005,20006,20007,20008,20009,20010,20011,20012,20013,20014,20015,20016,20017,20018,20019,20020,20021,20022,20023,20024,20025,20026,20027,20028,20029,20030,30001,30002,30003,30004,30005,30006,30007,30008,30009,30010,30011,30012,30013,30014,30015,30016,30017,30018,30019,30020,30021,30022,30023,30024,30025,30026,30027,30028,30029,30030,40001,40002,40003,40004,40005,40006,40007,40008,40009,50000,10001,10002,10003,10004,10005,10006,10007,10008,10009,10010,10011,10012,10013,10014,10015,10016,10017,10018,10019,10020,10021,10022,10023,10024,10025,10026,10027,10028,10029,10030,20001,20002,20003,20004,20005,20006,20007,20008,20009,20010,20011,20012,20013,20014,20015,20016,20017,20018,20019,20020,20021,20022,20023,20024,20025,20026,20027,20028,20029,20030,30001,30002,30003,30004,30005,30006,30007,30008,30009,30010,30011,30012,30013,30014,30015,30016,30017,30018,30019,30020,30021,30022,30023,30024,30025,30026,30027,30028,30029,30030,40001,40002,40003,40004,50005,40006,40007,40008,40009,50000};
        sensor.reset();
        delay(500);
        sensor.begin(pw1600, i50, sr100 );
        delay(300);
        uint32_t x[300];
         for (int ttt=0;ttt<80 ; ttt++){
          sensor.readSensor();
          //x[tt]=sensor.IR;
          //Serial.println(x[tt]);
          delay(10);
        }
        for (int tt=0;tt<300 ; tt++){
          sensor.readSensor();
          x[tt]=sensor.IR;
          //Serial.println(x[tt]);
          delay(10);
        }
        
        uint8_t buffer2[1200];
        for (int k=0 ; k<300 ;k++){ 
          uint8_t x1 = (x[k] & 0xff000000) >> 24;
          buffer2[k*4] =x1;
          uint8_t x2 = (x[k] & 0x00ff0000) >> 16;
          buffer2[k*4+1] =x2;
          uint8_t x3 = (x[k] & 0x0000ff00) >> 8;
          buffer2[k*4+2] =x3;
          uint8_t x4 = (x[k] & 0x000000ff);
          buffer2[k*4+3] =x4;
        }

        double_buzzer(100);
        
        //uint8_t buffer2[4] = {x1,x2,x3,x4};
        if(wifi.send(mux_id, buffer2, 1200)) {
            Serial.print("send back ok\r\n");
            //double_buzzer(100);

            
            
        } else {
            Serial.print("send back err\r\n");
            //buzzer(1500);
        }
 
        //delay(500);
        /*
        if (wifi.releaseTCP(mux_id)) {
            Serial.print("release tcp ");
            Serial.print(mux_id);
            Serial.println(" ok");
        } else {
            Serial.print("release tcp");
            Serial.print(mux_id);
            Serial.println(" err");
        }
        */
/*
        delay(3000);
        if (wifi.stopServer()){
          Serial.print("stop tcp server OK\r\n");
        }else{
          Serial.print("stop tcp server err\r\n");
        }
        delay(500);
        
        if (wifi.startTCPServer(8090)) {
        Serial.print("start tcp server ok\r\n");
        } else {
            Serial.print("start tcp server err\r\n");
            buzzer(1500);
        }
        
        if (wifi.setTCPServerTimeout(10)) { 
            Serial.print("set tcp server timout 10 seconds\r\n");
        } else {
            Serial.print("set tcp server timout err\r\n");
            buzzer(1500);
        }
    
     */   

    
        delay(500);
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        delay(500);
    }




    
}

void buzzer(int time){
  digitalWrite(BUZZER,HIGH);
  delay(time);
  digitalWrite(BUZZER,LOW);
}

void double_buzzer(int time){
  digitalWrite(BUZZER,HIGH);
  delay(time);
  digitalWrite(BUZZER,LOW);
  delay(time);
  digitalWrite(BUZZER,HIGH);
  delay(time);
  digitalWrite(BUZZER,LOW);
  delay(time);
}
        
