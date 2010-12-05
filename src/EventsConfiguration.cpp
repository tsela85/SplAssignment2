// EventsConfiguration.cpp

#include <sstream>

#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"

#include "EventsConfiguration.h"
#include "AppLogger.h"

using namespace Poco;
using namespace Poco::Util;
using namespace std;

CEventsConfiguration::MyEvent::MyEvent(DateTime inDate, std::string inDescription)
{
        mDateOfOccurence = inDate;
        mDescription = inDescription;
}

// Constructor that receive data stream as std::istream
CEventsConfiguration::CEventsConfiguration(std::istream& istr) : IniFileConfiguration(istr)
{
        Construct();
}

// Constructor that receive path as std::string
CEventsConfiguration::CEventsConfiguration(const std::string& path) : IniFileConfiguration(path)
{
        Construct();
}

CEventsConfiguration::~CEventsConfiguration()
{
        vector<MyEvent*>::iterator iterator;

        // Deletes all MyEvents
    for(iterator = mMyEvents.begin();
                iterator != mMyEvents.end();
        iterator++)
        {
                if (*iterator != NULL)
                {
                        delete *iterator;
                }
        }
}

void CEventsConfiguration::Construct()
{
        // Reserve an initial size for my events vector,
        // so he can allocate in advance. If allocate
        mMyEvents.reserve(4);

        CAppLogger::Instance().Log("Reading events configuration file...", Message::PRIO_DEBUG);

        int currConfFileIndex = 1;
        bool quit = false;
        while (!quit)
        {
                try
                {
                        ostringstream dateKeyNameBuilder;
                        ostringstream eventKeyNameBuilder;

                        // Get event date
                        dateKeyNameBuilder << "date" << currConfFileIndex;
                        string dateStr = getString(dateKeyNameBuilder.str());

                        // Get event description
                        eventKeyNameBuilder << "event" << currConfFileIndex;
                        string desc = getString(eventKeyNameBuilder.str());

                        // If no exception is thrown, meaning everything is OK. Now we...:
                        // 1. Parse the date
                        int timeZoneDiff;
                        DateTime date;
                        if (!DateTimeParser::tryParse("%d/%n/%Y", dateStr, date, timeZoneDiff))
                        {
                                // Failed to parse date. quit.
                                quit = true;
                                continue;
                        }

                        // 2. Create the event.
                        MyEvent* eventPtr = new MyEvent(date, desc);

                        // 3. Add the event.
                        mMyEvents.push_back(eventPtr);

                        // 4. Increase event index
                        currConfFileIndex++;
                }
                catch (NotFoundException ex)
                {
                        quit = true;
                }
        }

        // Write to log
    CAppLogger::Instance().Log("Events configuration file read successful", Message::PRIO_DEBUG);
        ostringstream msg;
        msg << "No. of events:" << (int)mMyEvents.size();
        CAppLogger::Instance().Log(msg.str(), Message::PRIO_DEBUG);
}

CEventsConfiguration::MyEvent CEventsConfiguration::operator [] (int inIndex) const
{
        // Copy the contents of the requested my event
        // Note this is legal only in cases we have a copy constructor or we have a non pointer members.
        MyEvent result = *(mMyEvents[inIndex]);
        return result;
}

