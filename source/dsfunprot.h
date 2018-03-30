//dsfunprot.h -- define "datafiles" struct and prototype functions

#include <iostream>
#include <string>
#include <fstream>
#include <string>
using std::string;

#ifndef DATAFILENAME_STRUCT_
#define DATAFILENAME_STRUCT_

struct datafilenames
{
	int numfiles;
	string filenames[500];
};

// Prototye functions
datafilenames getfilenames(const char * sourcepath, const char * rawdatapath);
string & toISO(string &, string &, string &);
string toJSON(string filename, const char * rawdatapath, const char * jobdatapath, int filenum);
void toMongo(string, const char *);

#endif
