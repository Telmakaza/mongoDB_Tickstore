# callmongoimport.py -- call mongoimport in parallel
import os
import sys
from multiprocessing import Pool

# Take user input
datafilepath = sys.argv[1]

# Set data path and get files in directory
filenames = os.listdir(datafilepath)

# Import files in parallel
def mongoimportcmd(filename):
    exstr = "mongoimport -d BRICSData -c testTransactions  --type json --file " + datafilepath + "/" + filename
    print(exstr)
    os.system(exstr)
    fullfilename = datafilepath + "/" + filename
    #os.remove(fullfilename)

if __name__ == '__main__':
    with Pool() as p:
        p.map(mongoimportcmd, filenames)