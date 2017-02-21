// ##########  CLARDIA 1.0  - OLIVESCRIPT (PVT) LTD  ############


/* The wire connections
HX Module
white - vcc (+5)
grey - A1
purple - A0
blue - ground 

7 Segment Display
orange - ground
yellow - vcc (+5)
red - 4 
green - 3
brown - 2
*/


#include "HX711.h"
HX711 scale(A1, A0);                            // HX711.DOUT	- pin #A1  ,  HX711.PD_SCK	- pin #A0

#include <LedControl.h>
LedControl mydisplay = LedControl(4, 2, 3, 1);
unsigned int count = 0;
unsigned int count_one = 0;
unsigned int count_two = 0;

void setup() {
  
  Serial.begin(38400);
  Serial.println("CLARDIA DEMO");


  // initializing the scale......
  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided 
						// by the SCALE parameter (not set yet)  
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
						// by the SCALE parameter set with set_scale
  Serial.println("Readings:");


  //initializing the display
  mydisplay.shutdown(0, false);  // turns on display
  mydisplay.setIntensity(0, 15); // 15 = brightest
  mydisplay.setDigit(0, 0, 0, false);
  mydisplay.setDigit(0, 1, 0, false);
  mydisplay.setDigit(0, 2, 0, false);
  mydisplay.setDigit(0, 3, 0, false);
  mydisplay.setDigit(0, 4, 0, false);
  mydisplay.setDigit(0, 5, 0, false);
  mydisplay.setDigit(0, 6, 0, false);
  mydisplay.setDigit(0, 7, 0, false);
  
}

void loop() {
  //Serial.print("one reading:\t");
  float x = scale.get_units();
  //Serial.print(x, 1);
  //Serial.print("\t| average:\t");
  float y = scale.get_units(10);
  //Serial.println(y, 1);
  Serial.println("Actual Weight of the Person: ");
  Serial.println(y/10);

  
  //print the weight figure in the display
  printNumber(y);
  
  
  
  
  scale.power_down();			        // put the ADC in sleep mode
  delay(3000);
  scale.power_up();

}

void printNumber(float y) {  
  
  int integerPart = (int) y;          
  int decimal = integerPart%10;        
  integerPart = integerPart/10;        
  int ones = integerPart%10;          
  integerPart = integerPart/10;      
  int tens = integerPart%10;          
  integerPart = integerPart/10;        
  int hundreds = integerPart;
  
  
  mydisplay.setDigit(0,0,decimal,false);
  mydisplay.setDigit(0,1,ones,true);
  mydisplay.setDigit(0,2,tens,false);
  mydisplay.setDigit(0,3,hundreds,false); 
    
} 

