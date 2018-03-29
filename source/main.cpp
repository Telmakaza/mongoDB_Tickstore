/* DataEngineering/main.cpp -- Convert TRTH csv files into json files and import
to mongoDB database*/

#include "dsfunprot.h"
#include <iostream>
using::std::cout;
using std::endl;

int main(int argc, char ** instream)
{
    /* instream[0] = filename
       instream[1] = market
       instream[2] = source path
       instream[3] = raw data path
       instream[4] = job data path
    */
    
    // Get filenames
    datafilenames rawData = getfilenames(instream[1], instream[2], instream[3]);

    // Import convert files to json and import them to a mongoDB database;

    // Get number of files
    int n  = rawData.numfiles;
    cout << instream[1] << ": " << n << " files." << endl;
    for(int j = 0; j < rawData.numfiles; j++)
    {
        toJSON(rawData.filenames[j], instream[1], instream[3], instream[4], j);
        cout << "File 1 = " << rawData.filenames[j] << " converted to json" << endl;
    }

    // Call python import script
    string exstr = string("python3 ") + string(instream[2]) +  string("/DataEngineering/source/callmongoimport.py ") + string(instream[1]) + string(" ") + string(instream[4]);
    system(exstr.c_str());
    
}