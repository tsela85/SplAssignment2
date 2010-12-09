/*
 * Worker.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */
#include "../include/defs.h"
#include <vector>
//#include "../include/SkillType.h"
//#include "../include/JobType.h"

#ifndef WORKER_H_
#define WORKER_H_

class Worker {//TODO: is this necessary??

private:
	int ID;
	std::vector<int> skills;//[6]; // according to numbering in page 2.
	bool desiredJobTypes[6];
	int expectedSalary;
	Worker *origin;

public:
	/**
	 //	 * a new Worker contractor
	 */
	Worker(int ID, bool skills[6], bool desiredJobTypes[6], int expectedSalary);

	/**
	 * return a copy of this worker with a pointer to the origin (this Worker).
	 */
	Worker copy();

	/**
	 * return the Worker's ID
	 */
	int getID() {
		return ID;
	}

	/**
	 * return the Worker's skills
	 */
	std::vector<int> getSkills() {
		return skills;
	}

	/**
	 * return the Worker's desired job types
	 */
	int getDesiredJobTypes();

	/**
	 * return the Worker's expected salary
	 */
	int getExpectedSalary() {
		return expectedSalary;
	}

	/**
	 * return the Worker's origin in the HRC database
	 */
	Worker getOrigin();

	/**
	 * sets the Worker's origin worker in the HRC database
	 */
	void setOrigin();

};
#endif /* WORKER_H_ */
