/*
 * Worker.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */
#include "../include/defs.h"
#include "Poco/DateTime.h"
#ifndef WORKER_H_
#define WORKER_H_

class Worker {

private:
	int ID;
	int skills[6]; // according to numbering in page 2.
	bool desiredJobTypes[6];
	int expectedSalary;
	Poco::DateTime *time;
	Poco::DateTime inDate;
	Poco::DateTime outDate;
	bool occupied;

public:

	/** a new Worker contractor */
	Worker(int ID, int skills[6], bool desiredJobTypes[6], int expectedSalary,
			Poco::DateTime *time);

	/** a Worker destructor */
	~Worker();

	/** return the Worker's ID */
	int getID();

	/** return the Worker's skills */
	void getSkills(int skills[]);

	/** return the Worker's desired job types */
	void getDesiredJobTypes(bool _desiredJobTypes[]);

	/** return the Worker's expected salary */
	int getExpectedSalary();

	/** return the Worker's origin in the HRC database */
	Worker getOrigin();

	/** sets the Worker's origin worker in the HRC database */
	void setOrigin();

	/** returns the date the worker joined the HRC seekers database */
	Poco::DateTime getInDate();

	/** sets the date the worker left the HRC seekers database */
	void setOutDate();

	/** returns the date the worker left the HRC seekers database */
	Poco::DateTime getOutDate();

};
#endif /* WORKER_H_ */