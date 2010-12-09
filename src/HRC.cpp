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

/**
 * increment time by 1 day.
 */
void HRC::incDate() {
	time += Poco::Timespan(1, 0, 0, 0, 0);
}

void HRC::addCandidate(Worker w) {
	s_p_Worker workerPtr(new Worker(w));//new Worker(w));
	candidates.insert(std::make_pair(/*w.getID()*/6, workerPtr)); //FIXME: return the getID() function
	seekers.push_back(workerPtr);
}

void HRC::addJob(Job j) {
	s_p_Job jobPtr(new Job(j));
	jobs.insert(std::make_pair(j.SN, jobPtr));
	openings.push_back(jobPtr);
}

int HRC::compute_Company_Rep() {

}

void HRC::match(){}

s_p_Worker HRC::matchForJob(s_p_Job jobPtr){}
