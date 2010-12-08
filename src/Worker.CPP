/*
 * Worker.CPP
 *
 *  Created on: Dec 5, 2010
 *      Author: tom
 */

#include "Worker.h"

class Worker {

private:
	int ID;
	bool skills[6]; // according to numbering in page 2.
	bool desiredJobTypes[6];
	int expectedSalary;
	Worker *origin;


	Worker::Worker(int ID, bool skills[6], bool desiredJobTypes[6], int expectedSalary) {
		this.ID=ID;
		this.skills=skills;
		this.desiredJobTypes=desiredJobTypes;
		this.expectedSalary=expectedSalary;
		this.origin=null;
	}

	Worker copy() {
		Worker temp = new Worker(worker.getID(),worker.getskills(),worker.getdesiredJobTypes(),worker.getexpectedSalary());
		temp.setOrigin(this);
		return temp;
	}

	int getID() {
		return this.ID;
	}

	void getSkills(bool skills[]) {
		for (int i=0; i < 6; i++)
			skills[i]=this.skills[i];
	}

	void getDesiredJobTypes(bool desiredJobTypes[]) {
		for (int i=0; i < 6; i++)
			desiredJobTypes[i]=this.desiredJobTypes[i];
	}

	int getExpectedSalary(){
		return this.expectedSalary;
	}

	Worker getOrigin() {
		return this.origin;
	}

	void setOrigin(Worker worker) { // TODO: add to .h
		this.origin=worker;
	}

	Worker::~Worker() {
		delete(this.origin);
	}
}
