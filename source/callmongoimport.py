# callmongoimport.py -- call mongoimport in parallel
import os
import sys
from multiprocessing import Pool

# Take user input
Market = sys.argv[1]
datafilepath = sys.argv[2]

# Set data path and get files in directory
datafilepath = datafilepath + '/' + Market
filenames = os.listdir(datafilepath)

# Import files in parallel
def mongoimportcmd(filename):
    exstr = "mongoimport -d BRICSData2 -c " + Market + "Transactions " + "--type json --file " + datafilepath + "/" +filename
    os.system(exstr)
    fullfilename = datafilepath + "/" + filename
    #os.remove(fullfilename)

if __name__ == '__main__':
    with Pool() as p:
        p.map(mongoimportcmd, filenames)