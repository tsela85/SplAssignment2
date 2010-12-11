/*
 * Job.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */
#include "../include/defs.h"
#include "Poco/DateTime.h"
//#include "../include/SkillType.h"

#ifndef JOB_H_
#define JOB_H_
class Job {
public:
	int SN;
	bool skills[6];
	int CompanySN;
	int type;
	bool closed;
	Poco::DateTime inDate;
	Poco::DateTime outDate;
	long int days;

	Job(int SN, bool skills[], int CompanySN, int type, Poco::DateTime inDate);

	Job(const Job &job);

	void taken(Poco::DateTime now);

	long int comp_days(Poco::DateTime now);
};

#endif /* JOB_H_ */
