/*
 * Worker.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */
#include "../headers/defs.h"

#ifndef WORKER_H_
#define WORKER_H_


class Worker {

private:
	int ID;
	bool skills[6]; // according to numbering in page 2.
	bool desiredJobTypes[6];
	int expectedSalary;

public:

	/** a new Worker contractor */
	Worker(int ID, bool skills[6], bool desiredJobTypes[6], int expectedSalary);

	/** a Worker distractor */
	~Worker();

	/** return the Worker's ID */
	int getID();

	/** return the Worker's skills */
	void getSkills(bool skills[]);

	/** return the Worker's desired job types */
	void getDesiredJobTypes(bool _desiredJobTypes[]);

	/** return the Worker's expected salary */
	int getExpectedSalary();

	/** return the Worker's origin in the HRC database */
	Worker getOrigin();

	/** sets the Worker's origin worker in the HRC database */
	void setOrigin();

};
#endif /* WORKER_H_ */
