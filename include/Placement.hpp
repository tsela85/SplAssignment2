/*
 * Placement.hpp
 *
 *  Created on: Dec 9, 2010
 *      Author: Tom and Aviad
 */

#ifndef PLACEMENT_HPP_
#define PLACEMENT_HPP_

#include "../include/SkillType.h"
#include "../include/JobType.h"
#include "../include/defs.h"
#include "../include/HRC.h"

class Placement {
public:
	s_p_Worker worker;
	s_p_Job job;
	int salary;
	ass2::JobType jobType;
	ass2::SkillType skillType;
	Poco::DateTime date;

	Placement() {}

	Placement(s_p_Worker workerPtr, s_p_Job jobPtr, int job_type,
			int skill_type, Poco::DateTime time) {
		worker = workerPtr;
		job = jobPtr;
		salary = worker->getExpectedSalary();
		jobType = ass2::JobType(int2EJobType(job_type));
		skillType = ass2::SkillType(int2ESkillType(skill_type));
		date = time;
	}

};

#endif /* PLACEMENT_HPP_ */
