# getfilenames.py -- get file names of raw data and import them to c++
import os
import sys

# Get file names
Market = sys.argv[1];
datafilepath = sys.argv[2] + "/" + Market;
#datafilepath = 'C:/TRTH/RawData/' + Market
filenames = os.listdir(datafilepath)

# Write file names to text files
fobj = open('filenames' + Market + '.txt', 'w')
for name in filenames:
	fobj.write(name + "\n")

fobj.close()
