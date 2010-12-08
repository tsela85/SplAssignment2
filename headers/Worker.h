/*
 * Worker.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */
#include "../headers/defs.h"
#include "../headers/SkillType.h"
#include "../headers/JobType.h"

#ifndef WORKER_H_
#define WORKER_H_



class Worker {//TODO: is this necessary??

private:
	int ID;
	SkillType skills[6]; // according to numbering in page 2.
	JobType desiredJobTypes[6];
	int expectedSalary;
	Worker *origin;

public:
	/**
//	 * a new Worker contractor
	 */
	Worker(int ID, SkillType skills[6], JobType desiredJobTypes[6], int expectedSalary);

	/**
	 * return a copy of this worker with a pointer to the origin (this Worker).
	 */
	Worker copy();

	/**
	 * return the Worker's ID
	 */
	int getID();

	/**
	 * return the Worker's skills
	 */
	int getSkills();

	/**
	 * return the Worker's desired job types
	 */
	int getDesiredJobTypes();

	/**
	 * return the Worker's expected salary
	 */
	int getExpectedSalary();

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
