// csv_tojson.cpp -- Defines function that converts TRTH csv file to a JSON format
#include <fstream>
#include <string>
#include <stdio.h>
#include "dsfunprot.h"
#include <iostream>

using std::ofstream;
using std::ifstream;
using std::string;

// Bring rawdatapath and jobdatapath variables into scope
//extern string rawdatapath;
//extern string jobdatapath;

//string rawdatapath = "C:/TRTH/RawData/";
//string jobdatapath = "C:/TRTH/JobData/";
static char ch;
 
// define dummy variable to take inputs
string dummy;

inline void getwrite(const char * event, std::istream & inObj, std::ostream & outObj, char delim)
{// Get input from input file and write to outputfile

	getline(inObj, dummy, ',');
	outObj << event << ":" << "\"" << dummy << "\"" << delim;
}

inline void getwritenum(const char * event, std::istream & inObj, std::ostream & outObj, char delim)
{// Get input from input file and write to outputfile

	getline(inObj, dummy, ',');
	dummy.empty() ? dummy = "0": dummy;
	outObj << event << ":" << dummy << delim;
}

string toJSON(string filename, const char * rawdatapath, const char * jobdatapath, int filenum)
{
	// Declare file input and output objects
	ifstream fin;
	ofstream fout;

	// Associate file output object with an output file
	string outfile = string(jobdatapath) + string("/") + std::to_string(filenum) + string(".json");
	fout.open(outfile);
	
	// Associate file input object with an input file
	string infile = string(rawdatapath) + string("/") + filename;
	fin.open(infile);

	// Remove header from input stream
	getline(fin, dummy);

	// Declare variables for date, time gmtoffset and date-time
	string Date, Time, gmtOffset, DateTime;

	// Read input from input file and write it to output json file
	while(fin.good())
	{
			fout << "{";
			//getwrite("RIC", fin, fout, ','); // Get and write RIC

			// Get date time and write to file
			getline(fin, Date, ',');
			getline(fin, Time, ',');
			getline(fin, gmtOffset, ',');
			DateTime = toISO(Date, Time, gmtOffset);
			fout << "DateTime:" << "{$date:" << "\""<< DateTime << "\"" << "}" << ",";

			// Get transaction an quote prices and volumes and write to json file
			getwrite("Type", fin, fout, ',');
			getwritenum("Price", fin, fout, ',');
			getwritenum("Volume", fin, fout, ',');
			getline(fin, dummy, ','); // Remove market vwap from input stream
			getwritenum("BidPrice", fin, fout, ',');
			getwritenum("BidVolume", fin, fout, ',');
			getwritenum("AskPrice", fin, fout, ',');
			getwritenum("AskVolume", fin, fout, '}');
			fout << '\n';

			// Remove excess data from input stream
			getline(fin, dummy);
	}
	
	
	fout.close();
	
	return outfile;
}


