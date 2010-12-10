/*
 * HRC.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */

#ifndef HRC_H_
#define HRC_H_

#include <map>
#include <set>
#include <vector>
#include <memory>
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"
#include "../include/Worker.h"
#include "../include/Job.h"
#include "../include/Company.h"
#include "../include/Placement.h"
#include <boost/ptr_container/ptr_list.hpp>
#include "../include/defs.h"

typedef boost::shared_ptr<Company> s_p_Company;

class HRC {
private:
	std::map<int, s_p_Worker> workers;
	std::map<int, s_p_Job> jobs;
	std::map<int, s_p_Company> companies;
	std::list<s_p_Worker> seekers;
	std::list<s_p_Job> openings;
	long profit;
//	Placement del_me;
	Poco::DateTime time;
	int Company_Rep;
	int Seeker_rep;
	int strategy;
	vector<set<Worker> > placementsBySkillType;
	vector<set<Placement> > placementsByJobType; //FIXME: should be 'Placement'

public:

	HRC();

	HRC(Poco::DateTime sDate);

	void setDate(Poco::DateTime newDate);

	void incDate();

	void addCandidate(Worker w);

	void addJob(Job j);

	int getStrategy() {
		return strategy;
	}

	void setStrategy(int s) {
		strategy = s;
	}

	int compute_Company_Rep();

	void match();

	bool matchForJob(s_p_Job jobPtr, s_p_Worker workerPtr);

	void candidate_placement(s_p_Worker placedWorker, s_p_Job job);

	void copySkills(vector<bool> skills, int size, Worker worker);

	vector<s_p_Worker> getApplicants(s_p_Job jobPtr);

	bool screenApplicants(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker choosenOne);

	bool screenApplicantsCheap(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker choosenOne);

	bool screenApplicantsLavish(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker choosenOne);

	bool screenApplicantsCostEffective(s_p_Job jobPtr,
			vector<s_p_Worker> applicants, s_p_Worker choosenOne);

	bool compareSalaries(s_p_Worker* w1, s_p_Worker* w2);

	float QL(s_p_Worker worker, Job job);

//	std::string int2EJobType(int type);
};



#endif /* HRC_H_ */
