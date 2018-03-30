// getfilenames.cpp -- reads file names from a csv file and saves them to a struct

#include <stdio.h>
#include <string.h>
#include <fstream>
#include "dsfunprot.h"
using std::ifstream;
using std::ofstream;
using std::string;


datafilenames getfilenames(const char * sourcepath, const char * rawdatapath)
{
	// Allocate memory space
	char exstr[1024];

	// Copy execution string to allocated memory space
	strcpy(exstr, "python3 ");
	strcat(exstr, sourcepath);
	strcat(exstr, "/mongoDB_Tickstore/source/getfilenames.py ");
	strcat(exstr, " ");
	strcat(exstr, rawdatapath);
	system(exstr);

	// Read file names from input file
	ifstream infnames;
	string file_on_sys = string(rawdatapath) + string("/filenames.txt");
	infnames.open(file_on_sys);

	// Count number of files and store names
	string files[500];
	int counter = 0;
	while(infnames.good())
	{
		getline(infnames, files[counter]);
		++counter;
	}

	// Declare datafilenames struct
	datafilenames dfstruct;

	// Initailise datafilenames struct
	dfstruct.numfiles = counter - 1;
	for(int i = 0; i < counter; i++)
	{
		dfstruct.filenames[i] = files[i];
	}

	infnames.close();
	remove(file_on_sys.c_str());

	return dfstruct;
}
