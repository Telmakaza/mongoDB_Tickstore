# importdata.py -- import TRTH data into BRICSData database
import os
from multiprocessing import Pool

exchanges = ["BSE"]
sourcepath = input("Please enter the path to the DataEngineering folder: ")
print("-------------------------------------------------------------")
print("Thank you. Two more user inputs needed.")
rawdatapath = input("Please enter the path to the raw data folder: ")
print("------------------------------------------------------------------")
print("Thank you. One more user input needed. Please enter the directory in which job data will be stored (and subsequently deleted).")
jobdatapath = input("This needs to be an empty folder: ")
print("-------------------------------------------------------------")
print("Thank you. All user inputs taken. Please wait for your data to be processed...")

def importmarketdata(market):
    os.system(sourcepath + "/DataEngineering/bin/main " + market + " " + sourcepath + " " + rawdatapath + " " + jobdatapath) 

if __name__ == '__main__':
    with Pool(3) as p:
        p.map(importmarketdata, exchanges)


print("-----------------------------------------------------------")
print("Data importation process complete.")