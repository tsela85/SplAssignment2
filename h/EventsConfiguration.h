// EventsConfiguration.h

#ifndef EVENTS_CONFIGURATION_H
#define EVENTS_CONFIGURATION_H

#include <string>
#include <vector>

#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"

class CEventsConfiguration : public Poco::Util::IniFileConfiguration
{
public:
        struct MyEvent
        {
                MyEvent(Poco::DateTime inDate, std::string inDescription);

                Poco::DateTime  mDateOfOccurence;
                std::string             mDescription;
        };

        // Constructors :
        /////////////////////////////////////////////////////////////////////////
        // Constructor that receive data stream as std::istream
        CEventsConfiguration(std::istream& istr);

        // Constructor that receive path as std::string
        CEventsConfiguration(const std::string& path);
        /////////////////////////////////////////////////////////////////////////

        // Destructor
        virtual ~CEventsConfiguration();

        // Operator to get my events by index
        CEventsConfiguration::MyEvent operator [] (int inIndex) const ;

        // Get count of my event
        size_t GetMyEventsCount() const {return mMyEvents.size();}
private:
        // Method that actually performs constructors code.
        // Exist to prevent code duplication.
        void Construct();

        std::vector<MyEvent*> mMyEvents;
};

#endif //

