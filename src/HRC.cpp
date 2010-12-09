/*
 * HRC.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: Tom and Aviad
 */

#include "../include/HRC.h"
#include <algorithm>

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

void HRC::match() {
	for (list<s_p_Job>::iterator it = openings.begin(); it != openings.end(); ++it) {
		s_p_Worker placedWorker;
		if (matchForJob(*it, placedWorker)) {
			candidate_placement(placedWorker, *it);
		}
	}

}
void HRC::candidate_placement(s_p_Worker placedWorker, s_p_Job job) {

}

/**
 * copy the bool array of Worker w into bool into[]
 */
void HRC::copySkills(vector<bool> into, int size, Worker w) {
}
//	bool orig(w.getSkills());
//	for (int i = 0; i < size; ++i) {
//		into.push_back(orig[i]);
////	}
//}

bool HRC::matchForJob(s_p_Job jobPtr, s_p_Worker choosenOne) {
	vector<s_p_Worker> applicants;
	applicants = getApplicants(jobPtr);
	if (applicants.size() > 0) {
		choosenOne = screenApplicants(jobPtr, applicants);
		return true;
	} else {
		return false;
	}

}

vector<s_p_Worker> HRC::getApplicants(s_p_Job jobPtr) {
	vector<s_p_Worker> applicants;
	Job job = *jobPtr;
	std::vector<bool> desired;
	for (int j = 0; j < 6; ++j) {
		desired.push_back(job.skills[j]);
	}
	for (list<s_p_Worker>::iterator it = seekers.begin(); it != seekers.end(); ++it) {
		Worker worker = **it; //a list of pointers (s_p_Worker)
		vector<int> skills = worker.getSkills();
		//		copySkills(skills, 6, worker);
		bool workerFits = true;
		for (int i = 0; i < 6 && workerFits; ++i) {
			if (desired[i] && skills[i] == 0) {
				// this worker is laking skill[i] which is required
				workerFits = false;
			}
		}
		if (workerFits) {
			applicants.push_back(*it);
		}
	}
	return applicants;
}

s_p_Worker HRC::screenApplicants(s_p_Job jobPtr, vector<s_p_Worker> applicants) {
	// get company and company strategy
	int companySN = jobPtr->CompanySN;
	s_p_Company companyPtr = companies.find(companySN)->second;
	int recruitingPolicy = companyPtr->getRecruitingPolicy();
	if (recruitingPolicy == 0)
		return screenApplicantsCheap(jobPtr, applicants);
	else if (recruitingPolicy == 1)
		return screenApplicantsLavish(jobPtr, applicants);
	else
		return screenApplicantsCostEffective(jobPtr, applicants);
}

s_p_Worker HRC::screenApplicantsCheap(s_p_Job jobPtr,
		vector<s_p_Worker> applicants) {
	s_p_Worker choosenOne = *applicants.begin();
	int curMin = choosenOne->getExpectedSalary();
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		int tmp = (*it)->getExpectedSalary();
		if (tmp < curMin) {
			curMin = tmp;
			choosenOne = *it;
		} else if (tmp == curMin && ((*it)->getID() < choosenOne->getID())) {
			curMin = tmp;
			choosenOne = *it;
		}
	}
	return choosenOne;
}

s_p_Worker HRC::screenApplicantsLavish(s_p_Job jobPtr,
		vector<s_p_Worker> applicants) {
	s_p_Worker choosenOne = *applicants.begin();
	double curBest = QL(choosenOne, *jobPtr);
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		double tmp = QL(*it, *jobPtr);
		if (tmp > curBest) {
			curBest = tmp;
			choosenOne = *it;
		} else if (tmp == curBest && ((*it)->getID() < choosenOne->getID())) {
			curBest = tmp;
			choosenOne = *it;
		}
	}
	return choosenOne;
}

s_p_Worker HRC::screenApplicantsCostEffective(s_p_Job jobPtr,
		vector<s_p_Worker> applicants) {
	s_p_Worker choosenOne = *applicants.begin();
	double curBest = (QL(choosenOne, *jobPtr))
			/ choosenOne->getExpectedSalary();
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		double tmp = (QL(*it, *jobPtr)) / (*it)->getExpectedSalary();
		if (tmp > curBest) {
			curBest = tmp;
			choosenOne = *it;
		} else if (tmp == curBest && ((*it)->getID() < choosenOne->getID())) {
			curBest = tmp;
			choosenOne = *it;
		}
	}
	return choosenOne;
}

bool HRC::compareSalaries(s_p_Worker* w1, s_p_Worker* w2) {
	return ((*w1)->getExpectedSalary()) < ((*w2)->getExpectedSalary());
}

double HRC::QL(s_p_Worker worker, Job job) {
	vector<int> skills = worker->getSkills();
	float tot(0);
	float num(0);
	for (int j = 0; j < 6; ++j) {
		if (job.skills[j]) {
			tot += skills[j];
			num++;
		}
	}
	double ret;
	if (num > 0) {
		ret = tot / num;
	}
	return ret;
}
