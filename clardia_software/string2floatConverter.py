#Supporting Functions
#Using try exception because serial could be 
def string2floatConverter (x):
	try:
		number = float(x)
		return number
	except ValueError:
		pass