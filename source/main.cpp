/* DataEngineering/main.cpp -- Convert TRTH csv files into json files and import
to mongoDB database*/

#include "dsfunprot.h"
#include <iostream>
using::std::cout;
using std::endl;

int main(int argc, char ** instream)
{    
    // Get filenames
    datafilenames rawData = getfilenames(instream[1], instream[2]);

    // Get number of files
    int n  = rawData.numfiles;
    cout << instream[1] << ": " << n << " files." << endl;
    for(int j = 0; j < rawData.numfiles; j++)
    {
        toJSON(rawData.filenames[j], instream[2], instream[3], j);
        cout << "File 1 = " << rawData.filenames[j] << " converted to json" << endl;
    }

    // Call python import script
    string exstr = string("python3 ") + string(instream[1]) +  string("/mongoDB_Tickstore/source/callmongoimport.py ") + string(instream[3]);
    system(exstr.c_str());
    
}