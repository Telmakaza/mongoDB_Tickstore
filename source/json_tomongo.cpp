// toMongo.cpp -- import json files into mongo database

#include <stdio.h>
#include <string>
#include <iostream>
using std::string;

void toMongo(string fullfilename, const char * market)
{
    // Construct execution strin
    string exstr = string("mongoimport -d BRICSData -c ") + string(market) + string("Transactions") + string(" --type json --file ") + fullfilename;
    std::cout << exstr << std::endl;
    system(exstr.c_str());
}