# importdata.py -- import TRTH data into BRICSData database
import os
from multiprocessing import Pool

sourcepath = input("Please enter the path to the mongoDB_Tickstore repo: ")
print("-------------------------------------------------------------")
rawdatapath = input("Please enter the path to the raw data folder: ")
print("------------------------------------------------------------------")
print("Enter the directory in which job data must be stored (and subsequently deleted).")
jobdatapath = input("This needs to be an empty folder: ")
print("-------------------------------------------------------------")
print("All user inputs succesfully taken. Please wait for data to be processed...")

os.system(sourcepath + "/mongoDB_Tickstore/bin/main " + " " + sourcepath + " " + rawdatapath + " " + jobdatapath) 

print("-----------------------------------------------------------")
print("Data importation process complete.")