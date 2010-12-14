/*
 * Worker.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */


#include "../include/defs.h"
#include "Poco/DateTime.h"
#include "../include/AppLogger.h"


#ifndef WORKER_H_
#define WORKER_H_
class Worker {

private:
	int ID;
	int skills[6]; // according to numbering in page 2.
	bool desiredJobTypes[6];
	float expectedSalary;
	float originSalary;
	Poco::DateTime *time;
	Poco::DateTime inDate;
	Poco::DateTime outDate;
	long int days;
	bool occupied;
	CAppLogger *logger;

public:

	/** a new Worker contractor */
	Worker(int ID, int skills[6], bool desiredJobTypes[6], float expectedSalary,
			Poco::DateTime *time, CAppLogger *logger);

	/** a Worker destructor */
	~Worker();

	/** return the Worker's ID */
	int getID();

	/** return the Worker's skills */
	void getSkills(int skills[]);

	/** return the Worker's desired job types */
	void getDesiredJobTypes(bool _desiredJobTypes[]);

	/** return the Worker's expected salary */
	float getExpectedSalary();

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

	/** updates the workers expectedSalary according to the date he joined */
	bool compromise();

	/** this worker is hired. Hurray! */
	void hired();

	/** compute the number of days the worker spent in the HRC database */
	long int comp_days();

	/** has this worker found a job yet? */
	bool isOccupied();
};
#endif /* WORKER_H_ */
