/*
 * Worker.CPP
 *
 *  Created on: Dec 5, 2010
 *      Author: tom
 */

#include "../headers/Worker.h"


	Worker::Worker(int _ID, bool _skills[6], bool _desiredJobTypes[6], int _expectedSalary) {
		ID=_ID;
		for (int i=0;i < 6;i++ ) {
			skills[i]=_skills[i];
			desiredJobTypes[i]=_desiredJobTypes[i];
		}
		expectedSalary=_expectedSalary;
	}

	int Worker::getID() {
		return ID;
	}

	void Worker::getSkills(bool _skills[]) {
		for (int i=0; i < 6; i++)
			_skills[i]=skills[i];
	}

	void Worker::getDesiredJobTypes(bool _desiredJobTypes[]) {
		for (int i=0; i < 6; i++)
			_desiredJobTypes[i]=desiredJobTypes[i];
	}

	int Worker::getExpectedSalary(){
		return expectedSalary;
	}


	Worker::~Worker()
	{
	}

