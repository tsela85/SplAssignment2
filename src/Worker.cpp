/*
 * Worker.CPP
 *
 *  Created on: Dec 5, 2010
 *      Author: tom
 */

#include "../include/Worker.h"

Worker::Worker(int _ID, int _skills[6], bool _desiredJobTypes[6],
		float _expectedSalary, Poco::DateTime *_time) {
	ID = _ID;
	for (int i = 0; i < 6; i++) {
		skills[i] = _skills[i];
		desiredJobTypes[i] = _desiredJobTypes[i];
	}
	originSalary = expectedSalary = _expectedSalary;
	time = _time;
	inDate = *_time;
//	outDate = null;
	occupied = false;
}

int Worker::getID() {
	return ID;
}

void Worker::getSkills(int _skills[]) {
	for (int i = 0; i < 6; i++)
		_skills[i] = skills[i];
}

void Worker::getDesiredJobTypes(bool _desiredJobTypes[]) {
	for (int i = 0; i < 6; i++)
		_desiredJobTypes[i] = desiredJobTypes[i];
}

float Worker::getExpectedSalary() {
	return expectedSalary;
}

Poco::DateTime Worker::getInDate() {
	return inDate;
}

void Worker::setOutDate() {
	outDate = *time;
}

Poco::DateTime Worker::getOutDate() {
	return outDate;
}

bool Worker::compromise() {
	int dayDiff = (*time-inDate).days();
	switch (dayDiff) {
		case 30: expectedSalary = (0.9)*originSalary; return true;
		case 60: expectedSalary = (0.8)*originSalary; return true;
		case 90: expectedSalary = (0.7)*originSalary; return true;
		default: return ((dayDiff < 90) ? true : false);
	}
}


Worker::~Worker() {
	delete (time);
}

