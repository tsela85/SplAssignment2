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

class Placement {
public:
	s_p_Worker worker;
	s_p_Job job;
	int salary;
	//	JobType job_type;
	//	const SkillType skillType;
	Placement(s_p_Worker workerPtr, s_p_Job jobPtr) {
		worker = workerPtr;
		job = jobPtr;
		salary = worker->getExpectedSalary();
	}

};

#endif /* PLACEMENT_HPP_ */
