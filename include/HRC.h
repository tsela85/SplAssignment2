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

typedef std::auto_ptr<Worker> auto_p_Worker;
typedef boost::shared_ptr<Worker> share_p_Worker;
typedef std::auto_ptr<Company> auto_p_Company;
typedef boost::shared_ptr<Company> share_p_Company;
typedef std::auto_ptr<Job> auto_p_Job;
typedef boost::shared_ptr<Job> share_p_Job;

class HRC {
private:
	std::map<int, Worker> candidates;
	std::map<int, Job> jobs;
	std::map<int, Company> companies;
	std::vector<Worker> seekers;
	std::vector<Job> openings;
	long profit;
	Poco::DateTime time;

public:
	HRC();

	HRC(Poco::DateTime sDate);

	void setDate(Poco::DateTime newDate);

	void incDate();

	void addCandidate(Worker w);

	void addJob(Job j);
};

#endif /* HRC_H_ */
