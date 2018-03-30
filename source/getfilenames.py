# getfilenames.py -- get file names of raw data and import them to c++
import os
import sys

# Get file names
datafilepath = sys.argv[1];
filenames = os.listdir(datafilepath)

# Write file names to text files
fobj = open(datafilepath + '/filenames.txt', 'w')
for name in filenames:
	fobj.write(name + "\n")

fobj.close()
