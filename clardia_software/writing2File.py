def writing2File (fileName , Mode , array):
	f = open( fileName , Mode)
	for  i in array:
		f.write(str(i))
		f.write("\n")

	f.close()

