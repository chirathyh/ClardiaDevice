# Clardia - Comprehensive Family Health Assistant , copyright (c) Olivescript < olivescript.com>
# by Chirath Hettiarachchi
# This is a connector to obtain the serial input from the Clardia Platform Prototype 1.0



import serial
import sys
import re

#Supporting Functions
#Using try exception because serial could be 
def string2floatConverter (x):
	try:
		number = float(x)
		return number
	except ValueError:
		pass

def writing2File (fileName , Mode , array):
	f = open( fileName , Mode)
	for  i in array:
		f.write(str(i))
		f.write("\n")

	f.close()


def connector ():
	#CONFIGURE
	DATAPOINTS = 10000
	ser = serial.Serial('/dev/cu.usbmodem1411', 115200)
	print "Clardia Platform Connector Running......"
	flag = False
	dataPoints = 0
	#Heart in bpm, SpO2 in %, Temperature in C. 
	PPG_RED = []
	PPG_IR = []
	#Order = Heart Rate, SpO2, Temperature
	GENERAL_PARAMETERS = [0,0,0]
	HEART_RATE = []

	while True:
		temp = ser.readline()
		temp2 = temp.split("\r")
		if (temp2[0] ==  "Beat!"):
			print "Starting to record the health parameters....."
			flag = True
		
		while flag:
			if (dataPoints > DATAPOINTS ):
				print "Health Parameters Successfuly Obtained."
				print "The General Parameters [ Heart Rate | SpO2 | Temperature ]"
				print GENERAL_PARAMETERS
				#print HEART_RATE
				print "The PPG RED Readings Array"
				#print PPG_RED
				writing2File('PPG_RED.txt', 'w',PPG_RED)
				print "The PPG IR Readings Array"
				#print PPG_IR
				sys.exit()
			temp = ser.readline()

			#TODO - CHECK WHY MULTIPLE DELIMETER IS NOT WORKING
		
			array = temp.split(":")
		
			#This is the GENERAL PARAMETERS
			if (len(array) == 6):
				array[1] = string2floatConverter(array[1])
				GENERAL_PARAMETERS[0] = array[1]
				HEART_RATE.append(array[1])
				array[3] = string2floatConverter(array[3])
				GENERAL_PARAMETERS[1] = array[3]
				array[5] = string2floatConverter(array[5])
				GENERAL_PARAMETERS[2] = array[5]

			#TODO -  im not taking any average from the serial data flow of general param just taking the final set of value hoping  that the values have stabilized, try other method

			if (len(array) == 2):
				aa = array[1]
				tempArray = aa.split(",")
				tempArray[0] = string2floatConverter(tempArray[0])
				PPG_RED.append(tempArray[0])
				bb = tempArray[1]
				bb = bb.replace('\r','')
				bb = bb.replace('\n','')
				bb = string2floatConverter(bb)
				PPG_IR.append(bb)
		
			dataPoints = dataPoints + 1

#the main loop ends




