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
	cofFile.getCompanies(&companies);
	ReadFile cofFile(argv[1]);
	vector<s_p_Worker> workers;
	cofFile.getWorkers(&workers);

	vector<s_p_Job> jobs;
	cofFile.getJobs(&jobs);

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
}

