/*Wiring to your Arduino
 example.ino
 this example plots PPG on GUI created by processing
 Hooking-up with the Arduino
----------------------
|Pulse pin label  | Pin Function         |Arduino Connection|
|-----------------|:--------------------:|-----------------:|
| VCC             | Supply               |  +5V             |             
| SCL             | Serial clock         |  A5              |
| SDA             | Serial data          |  A4              |
| GND             |                      |  GND             |
-------------------------------------------------------------
*/

#include "Protocentral_MAX30100.h"
#include <Wire.h>

MAX30100 sensor;
uint8_t data_len=8;
uint8_t DataPacketHeader[15];
volatile  long IRR,REDD;

volatile long red [300];
volatile long ir [300];
int i=0;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  while(!Serial);
  sensor.begin(pw1600, i50, sr100 );
  sensor.printRegisters();
}

void loop() {
   sensor.readSensor();
    IRR=sensor.IR;
    REDD=sensor.RED;
    DataPacketHeader[0] = 0x0A;
    DataPacketHeader[1] = 0xFA;
    DataPacketHeader[2] = (uint8_t) (data_len);
    DataPacketHeader[3] = (uint8_t) (data_len>>8);
    DataPacketHeader[4] = 0x02;
    
 
    DataPacketHeader[5] = REDD;
    DataPacketHeader[6] = REDD>>8;
    DataPacketHeader[7] = REDD>>16;
    DataPacketHeader[8] = REDD>>24; 

    
    DataPacketHeader[9] = IRR;
    DataPacketHeader[10] = IRR>>8;
    DataPacketHeader[11] = IRR>>16;
    DataPacketHeader[12] = IRR>>24; 

    DataPacketHeader[13] = 0x00;
    DataPacketHeader[14] = 0x0b;

    for(int i=0; i<15; i++) // transmit the data
    {
       Serial.write(DataPacketHeader[i]);
     }

//Serial.println(sensor.getPartID());
  /*
  if (i<300) {
    red[i]=REDD;
    ir[i] = IRR;
  }
  else {
    Serial.println("Recoding done");
    //Serial.println ("\nRED\n");
    for (int k=0;k<300;k++){
      Serial.print(red[k]);
      Serial.print(",");
      Serial.print(ir[k]);
      Serial.println();
    }
    while (1){
      
    }
  }
  i++;
  Serial.println(); */
  /*
  Serial.println(REDD);
  Serial.println(IRR); */
  
  delay(10);
}

