# Clardia - Comprehensive Family Health Assistant , copyright (c) Olivescript < olivescript.com>
# by Chirath Hettiarachchi
#The database management of the clardia software

## Database Details of clardia
USER_NAME = "chiru"
PASSWORD = "chiru"
DATABASE = "clardia_test"
TABLE = "patient_info"

#Database fiels
# ID
# Date
# Gender
# Age
# Height
# BloodGroup
# Diabetics
# HighBloodPressure
# Cholestrol
# Kidney
# OtherDiseases
# Weight(kg)
# Temp(c)
# Spo2(%)
# HeartRate
# IR
# RED

#!/usr/bin/python
import MySQLdb



db = MySQLdb.connect("127.0.0.1","Admin","admin","clardia_test" )
cursor = db.cursor()
sql = """INSERT INTO patient_info(ID)
         VALUES (33333)"""
try:
   cursor.execute(sql)
   db.commit()
except:
   db.rollback()
db.close()