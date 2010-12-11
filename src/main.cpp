
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
    Poco::DateTime date;
    int jobNum;
    int workNum;
    int seekerRep;
    int companyRep;
    int HrcStrat;
    int logConP;
    int logFileP;
    cofFile.getConfig(&date,&jobNum,&workNum,&seekerRep,&companyRep,&HrcStrat,&logConP,&logFileP);

}

