/*
 * Job.cpp
 *
 *  Created on: Dec 11, 2010
 *      Author: Tom and Aviad
 */

#include "../include/Job.h"
#include <string.h>

/*int SN;
 bool skills[6];
 int CompanySN;
 int type;
 bool closed;
 Poco::DateTime inDate;
 Poco::DateTime outDate;
 long int days;*/

Job::Job(int _SN, bool _skills[], int _CompanySN, int _type,
		Poco::DateTime _inDate) {
	SN = _SN;
	memcpy(skills, _skills, 6);
	CompanySN = _CompanySN;
	type = _type;
	closed = false;
	inDate = _inDate;
	days = 0;
}

Job::Job(const Job &src_job) {
	SN = src_job.SN;
	memcpy(skills, src_job.skills, 6);
	CompanySN = src_job.CompanySN;
	type = src_job.type;
	closed = src_job.closed;
	inDate = src_job.inDate;
	days = src_job.days;
}

void Job::taken(Poco::DateTime now) {
	closed = true;
	outDate = now;
	days = (inDate - outDate).days();
}

long int Job::comp_days(Poco::DateTime now) {
	if (closed)
		return days;
	else
		//compute the no. of days in HRC database only if the job has not been taken yet.
		return (now - inDate).days();
}
