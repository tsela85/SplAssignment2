/*
 * Placement.cpp
 *
 *  Created on: Dec 9, 2010
 *      Author: Tom and Aviad
 */

#include "../include/Placement.h"

Placement::Placement() {}

Placement::Placement(s_p_Worker workerPtr, s_p_Job jobPtr, int job_type,
			int skill_type, Poco::DateTime time) {
		worker = workerPtr;
		job = jobPtr;
		salary = worker->getExpectedSalary();
		jobType = ass2::JobType(int2EJobType(job_type));
		skillType = ass2::SkillType(int2ESkillType(skill_type));
		date = time;
	}
