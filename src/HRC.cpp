/*
 * HRC.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: Tom and Aviad
 */

#include "../include/HRC.h"

HRC::HRC() {
	/*candidates();
	jobs();
	companies();*/
	profit = 0;
}

HRC::HRC(Poco::DateTime sDate) {
	HRC();
	time = sDate;
}

void HRC::setDate(Poco::DateTime newDate) {
	time = newDate;
}

void HRC::incDate() {
	time += Poco::Timespan(1,0,0,0,0);
}

void HRC::addCandidate(Worker w) {
	candidates.insert(std::make_pair(/*w.getID()*/6, w)); //FIXME: return the getID() function
	seekers.push_back(w);
}

void HRC::addJob(Job j) {
	jobs.insert(std::make_pair(j.SN, j));
	openings.push_back(j);
}
