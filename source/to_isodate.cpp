// readdata_functions.cpp -- defines functions that are required in the compilation of readdata.cpp
#include <iostream>
#include <string>

using std::string;

inline string & toDate(string & date, const char* month)
{// Convert "DD-MMM-YYYY" to "YYYY-MM-DD"
	date = date.substr(7, 4) + "-" + string(month) + "-" + date.substr(0, 2);
}

string & toISO(string & date, string & time, string & gmtOffset)
{
	if(gmtOffset.length() > 0)
    {
		switch (date[5])
		{
			case 'B': toDate(date, "02"); break; // Convert "FEB" to "02"

			case 'R': date[3] == 'M' ? toDate(date, "03") : toDate(date, "04"); break; // Convert "MAR" (resp. "APR") to "03" (resp. "04")

			case 'Y': toDate(date, "05"); break; // Convert "MAY" to "05"

			case 'N': date[4] == 'A'? toDate(date, "01"): toDate(date, "06"); break; // Convert "JAN" (resp. "JUN") yo "01" (resp "06")

			case 'L': toDate(date, "07"); break; // Convert "JUL" to "07"

			case 'G': toDate(date, "08"); break; // Convert "AUG" to "08"

			case 'P': toDate(date, "09"); break; // Convert "SEP" to "09"

			case 'T': toDate(date, "10"); break; // Convert "OCT" to "10"

			case 'V': toDate(date, "11"); break; // Convert "NOV" to "11"

			case 'C': toDate(date, "12"); break; // Convetr "DEC" to "12"

		}

		// Switch sign of GMTOffset
		gmtOffset[0] == '+' ?  gmtOffset[0] = '-': gmtOffset[0] = '+';

		// Change date to ISODate
		date += "T" + time + gmtOffset.substr(0, 1) + "0" + gmtOffset.substr(1,1) + "00";
		return date;
	}

	return date;
	
}
