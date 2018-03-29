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
datafilenames getfilenames(const char *, const char *, const char *);
string & toISO(string &, string &, string &);
string toJSON(string, const char *, const char *, const char *, int);
void toMongo(string, const char *);

#endif
