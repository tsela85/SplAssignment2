// main.cpp

#include <iostream>

using namespace std;

#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"

#include "../include/ReadFile.h"
#include "../h/AppLogger.h"
#include "boost/shared_ptr.hpp"
#include "../include/HRC.h"
#include "../include/defs.h"

int main(int argc, char** argv) {

	ReadFile cofFile(argv[1]);
	cout << argv[1] << endl;
	Poco::DateTime date;
	int jobNum;
	int workNum;
	int seekerRep;
	int companyRep;
	int HrcStrat;
	int logConP;
	int logFileP;
	cofFile.getConfig(&date, &jobNum, &workNum, &seekerRep, &companyRep,
			&HrcStrat, &logConP, &logFileP); //TODO: add try/catch block for exceptions to be logged.

	CAppLogger logger(logConP, logFileP);

	HRC hrc = HRC(&date, seekerRep, companyRep, HrcStrat, &logger);
	vector<s_p_Company> companies;

//	cofFile.getCompanies(&companies); FIXME: uncomment

	vector<s_p_Worker> workers;
	cofFile.getWorkers(&workers);

	vector<s_p_Job> jobs;
//	cofFile.getJobs(&jobs); FIXME: uncomment

	for (vector<s_p_Company>::iterator it = companies.begin(); it
			!= companies.end(); it++) {
		hrc.addCompany(*it);
	}
	vector<s_p_Worker>::iterator worker_iterator = workers.begin();
	vector<s_p_Job>::iterator job_iterator = jobs.begin();
	for (int i = 0; i < workNum; i++) {
		hrc.addCandidate(*worker_iterator);
		worker_iterator++;
	}
	for (int j = 0; j < jobNum; j++) {
		hrc.addJob(*job_iterator);
	}
	bool terminate = false;
	while (!terminate) {
		hrc.incDate();
		hrc.compromise();
		int new_workers = hrc.get_seeker_rep();
		for (int addw = 0; addw < new_workers; addw++) {
			hrc.addCandidate(*worker_iterator);
			worker_iterator++;
		}
		int new_jobs = hrc.get_company_rep();
		for (int addj = 0; addj < new_jobs; addj++) {
			hrc.addJob(*job_iterator);
			job_iterator++;
		}

	}
	/*Poco::DateTime INITIAL_DATE(1999, 12, 31);
	 int INIT_JOBS_NUM = 3;
	 int INIT_CANDS_NUM = 4;
	 int INIT_SEEKER_REP = 3;
	 int INIT_COMPANY_REP = 1;
	 int HRC_STRATEGY = 0;
	 int LOGGER_CONSOLE_PRIORITY = 8;
	 int LOGGER_FILE_PRIORITY = 8;*/

	//	CAppLogger *logger_ptr = &logger;
	//	s_p_Worker worker;
	//	int skills[6] = { 2, 3, 4, 4, 0, 0 };
	//	bool desired[6] = { true, true, false, false, false, false };
	//	s_p_Worker worker(new Worker(234, skills, desired, 192.3456, &INITIAL_DATE,
	//			&logger));
	//	hrc.addCandidate(worker);
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

