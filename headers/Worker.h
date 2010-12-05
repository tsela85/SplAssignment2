/*
 * Worker.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */
#include "../headers/defs.h"

#ifndef WORKER_H_
#define WORKER_H_



class Worker {//TODO: is this necessary??
private:
	int ID;
	bool skills[6]; // according to numbering in page 2.
	bool desiredJobTypes[6];
	int expectedSalary;
	Worker *origin;

public:
	Worker(int ID, bool skills[6], bool desiredJobTypes[6], int expectedSalary);

	/**
	 * return a copy of this worker with a pointer to the origin (this Worker).
	 */
	Worker copy(Worker worker);

};
#endif /* WORKER_H_ */
