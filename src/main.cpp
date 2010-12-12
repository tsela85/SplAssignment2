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

	string file = argv[1];
	try {
		ReadFile cofFile(file);

		//	cout << argv[1] << endl;
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

		file = argv[2];
		ReadFile cofFile2(file);
		vector<s_p_Company> companies;
		cofFile2.getCompanies(&companies);

		file = argv[3];
		ReadFile cofFile3(file);
		vector<s_p_Worker> workers;
		cofFile3.getWorkers(&workers, &date, &logger);

		file = argv[4];
		ReadFile cofFile4(file);
		vector<s_p_Job> jobs;
		cofFile4.getJobs(&jobs);

		file = argv[5];
		ReadFile cofFile5(file);
		vector<Command> commands;
		cofFile5.getCommands(&commands);

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
			job_iterator++;
		}
		int new_workers(0), new_jobs(0);

		bool terminate = false;
		while (!terminate) {
			hrc.incDate();
			hrc.compromise();
			new_workers = hrc.get_seeker_rep();
			for (int addw = 0; addw < new_workers; addw++) {
				hrc.addCandidate(*worker_iterator);
				worker_iterator++;
			}
			new_jobs = hrc.get_company_rep();
			for (int addj = 0; addj < new_jobs; addj++) {
				hrc.addJob(*job_iterator);
				job_iterator++;
			}
			hrc.match();
			// TODO: execute commands
			if (hrc.is_last_day()) {
				hrc.update_Seeker_Rep();
				hrc.update_Company_Rep();
			}
		}

		logger.Log("testing", Poco::Message::PRIO_FATAL);

		return 0;
	} catch (Poco::FileNotFoundException) {
		CAppLogger logger(8, 8);
		ostringstream msg;
		msg << "Error: " << file << " file not found.";
		logger.Log(msg, Poco::Message::PRIO_CRITICAL);
		return 1;
	} catch (Poco::NotFoundException) {
		CAppLogger logger(8, 8);
		ostringstream msg;
		msg << "Error reading " << file << " file.";
		logger.Log(msg, Poco::Message::PRIO_CRITICAL);
		return 1;
	} catch (...) { //any other exception
		CAppLogger logger(8, 8);
		ostringstream msg;
		msg << "Error " << file.substr(0, file.find("."))
				/*just the name of the file*/<< " data is not consistent.";
		logger.Log(msg, Poco::Message::PRIO_ERROR);
		return 1;
	}
}

