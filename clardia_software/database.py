#!/usr/bin/python

import MySQLdb

field = "ID"
x = 12142


# Open database connection
db = MySQLdb.connect("127.0.0.1","chiru","chiru","clardia_test" )
#db=MySQLdb.connect(user="root",passwd="",db="clardia_test",unix_socket="/Applications/XAMPP/xamppfiles/var/mysql/mysql.sock")
# prepare a cursor object using cursor() method
cursor = db.cursor()
sql = """INSERT INTO patient_info(ID)
         VALUES (12121)"""
try:
   # Execute the SQL command
   cursor.execute(sql)
   # Commit your changes in the database
   db.commit()
except:
   # Rollback in case there is any error
   db.rollback()
# execute SQL query using execute() method.
cursor.execute("SELECT VERSION()")

# Fetch a single row using fetchone() method.
data = cursor.fetchone()

print "Database version : %s " % data

# disconnect from server
db.close()