// main.cpp

#include <iostream>

using namespace std;

#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"

#include "EventsConfiguration.h"
#include "AppLogger.h"

int main(int argc, char** argv)
{
        if (argc < 2)
        {
                cout << "Usage: " << argv[0] << "<configuration file name>" << endl;
                return 1;
        }

        // Load configuration (events' descriptions)
        CEventsConfiguration eventsConfFile(argv[1]);

        Poco::DateTime now;
        // Loop on all events and output days differences
        for (int i = 0; i < eventsConfFile.GetMyEventsCount(); i++)
        {
                CEventsConfiguration::MyEvent currEvent = eventsConfFile[i];
                std::ostringstream strStream;

                strStream << currEvent.mDescription << " was at " << Poco::DateTimeFormatter::format(currEvent.mDateOfOccurence.timestamp(), "%d/%n/%y");
                strStream << " and " << (now - currEvent.mDateOfOccurence).days() << " days has passed since than!";

                CAppLogger::Instance().Log(strStream, Poco::Message::PRIO_NOTICE);
        }

        return 0;
}
