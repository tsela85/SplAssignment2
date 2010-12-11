
// main.cpp

#include <iostream>

using namespace std;

#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"

#include "../include/ReadFile.h"
#include "../h/AppLogger.h"
#include <vector>

using namespace Poco;
using namespace Poco::Util;
using namespace std;

int main(int argc, char** argv)
{
    ReadFile cofFile(argv[1]);
    cout << argv[1]<< endl;
    Poco::DateTime date;
    int jobNum;
    int workNum;
    int seekerRep;
    int companyRep;
    int HrcStrat;
    int logConP;
    int logFileP;
    cofFile.getConfig(&date,&jobNum,&workNum,&seekerRep,&companyRep,&HrcStrat,&logConP,&logFileP);
    cout << jobNum << endl;
    cout <<workNum<< endl;
    cout <<seekerRep<< endl;
    cout <<companyRep<< endl;
    cout <<HrcStrat<< endl;
    cout <<logConP<< endl;
    cout <<logFileP<< endl;
}

