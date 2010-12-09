/*
 * HRC.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */

#ifndef HRC_H_
#define HRC_H_

#include <map>
#include <memory>
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"
#include "boost/shared_ptr.hpp"
#include "../include/Worker.h"
#include "../include/Job.h"
#include "../include/Company.h"
#include <boost/ptr_container/ptr_list.hpp>

typedef std::auto_ptr<Worker> a_p_Worker;
typedef boost::shared_ptr<Worker> s_p_Worker;
typedef std::auto_ptr<Company> a_p_Company;
typedef boost::shared_ptr<Company> s_p_Company;
typedef std::auto_ptr<Job> a_p_Job;
typedef boost::shared_ptr<Job> s_p_Job;

class HRC {
private:
	std::map<int, s_p_Worker> candidates;
	std::map<int, s_p_Job> jobs;
	std::map<int, s_p_Company> companies;
	std::list<s_p_Worker> seekers;
	std::list<s_p_Job> openings;
	long profit;
	Poco::DateTime time;
	int Company_Rep;
	int Seeker_rep;
	int strategy;

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

	s_p_Worker matchForJob(s_p_Job jobPtr);
};

#endif /* HRC_H_ */
