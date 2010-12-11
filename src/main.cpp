// main.cpp

#include <iostream>

using namespace std;

#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/LoggingFactory.h"
#include "Poco/Logger.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "../h/EventsConfiguration.h"
#include "../h/AppLogger.h"
#include "boost/shared_ptr.hpp"
#include "../include/HRC.h"
#include "../include/defs.h"

int main(int argc, char** argv) {

	Poco::DateTime INITIAL_DATE(1999, 12, 31);
	int INIT_JOBS_NUM = 3;
	int INIT_CANDS_NUM = 4;
	int INIT_SEEKER_REP = 3;
	int INIT_COMPANY_REP = 1;
	int HRC_STRATEGY = 0;
	int LOGGER_CONSOLE_PRIORITY = 3;
	int LOGGER_FILE_PRIORITY = 4;

	CAppLogger logger(LOGGER_CONSOLE_PRIORITY, LOGGER_FILE_PRIORITY);
//	CAppLogger *logger_ptr = &logger;
	HRC hrc = HRC(&INITIAL_DATE, INIT_SEEKER_REP, INIT_COMPANY_REP, HRC_STRATEGY, &logger);
//	s_p_Worker worker;
	int skills[6] = {2,3,4,4,0,0};
	bool desired[6] = {true, true, false, false, false,false};
	s_p_Worker worker(new Worker(234, skills, desired, 192.3456, &INITIAL_DATE, &logger));
	hrc.addCandidate(worker);
	logger.Log("testing", Poco::Message::PRIO_FATAL);

//	hrc.
//	CAppLogger::Instance().Log("testing", Poco::Message::PRIO_CRITICAL);
			/*//	Poco::
	Poco::Channel chnl = Poco::LoggingFactory::defaultFactory().createChannel("ConsoleChannel");
//	Poco::Logger console_logger = Poco::Logger::create("testLogger",
//			"Log.Console",
//			Poco::LoggingFactory::defaultFactory().createChannel(
//					"ConsoleChannel"), Poco::Message::PRIO_NOTICE);*/

	/*if (argc < 2) {
		cout << "Usage: " << argv[0] << "<configuration file name>" << endl;
		return 1;
	}

	// Load configuration (events' descriptions)
	CEventsConfiguration eventsConfFile(argv[1]);
	Poco::DateTime now;

	// Loop on all events and output days differences
	for (unsigned int i = 0; i < eventsConfFile.GetMyEventsCount(); i++) {
		CEventsConfiguration::MyEvent currEvent = eventsConfFile[i];
		std::ostringstream strStream;

		strStream << currEvent.mDescription << " was at "
				<< Poco::DateTimeFormatter::format(
						currEvent.mDateOfOccurence.timestamp(), "%d/%n/%y");
		strStream << " and " << (now - currEvent.mDateOfOccurence).days()
				<< " days has passed since than!";
*/
//		CAppLogger::Instance().Log(strStream, Poco::Message::PRIO_NOTICE);
//	}

	return 0;
}
