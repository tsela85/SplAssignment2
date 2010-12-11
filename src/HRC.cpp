/*
 * HRC.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: Tom and Aviad
 */

#include "../include/HRC.h"
#include <algorithm>
#include <limits>
#include "../include/JobType.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

typedef vector<s_p_Worker> v_p_Worker;

HRC::HRC() {
	/*candidates();
	 jobs();
	 companies();*/
	for (int i = 0; i < 6; ++i) {
		placementsByJobType.push_back(set<Placement, classcomp> ());
		placementsBySkillType.push_back(set<Placement, classcomp> ());
	}
	profit = 0;
	monthly_candidates = 0;
	monthly_jobs = 0;
	monthly_placements = 0;
	Aviad = "052978509";
	Tom = "37054244";
	reporter = HRCReport(Aviad, Tom);
	//	reporter(std::string("052978509"), std::string("37054244"));
}

HRC::HRC(Poco::DateTime sDate, int _Seeker_rep, int _Company_rep, int _strategy) {
	HRC();
	time = sDate;
	Seeker_Rep = _Seeker_rep;
	Company_Rep = _Company_rep;
	strategy = _strategy;
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
	s_p_Worker workerPtr(new Worker(w));
	workers.insert(std::make_pair(w.getID(), workerPtr));
	seekers.push_back(workerPtr);
	monthly_candidates++;
}

void HRC::addJob(Job j) {
	s_p_Job jobPtr(new Job(j));
	jobs.insert(std::make_pair(j.SN, jobPtr));
	openings.push_back(jobPtr);
	monthly_jobs++;
}

void HRC::update_Company_Rep() {
	float j, n, p;
	n = monthly_jobs;
	p = monthly_placements;
	j = (p / n) * 100;
	int delta = 0;
	if (j <= 33) {
		delta = -1;
	} else if (j >= 67) {
		delta = 1;
	}
	int new_rep = Company_Rep + delta;
	new_rep = std::min(5, new_rep);
	new_rep = std::max(1, new_rep);
	Company_Rep = new_rep;
}

void HRC::update_Seeker_Rep() {
	float c, n, p;
	n = monthly_candidates;
	p = monthly_placements;
	c = (p / n) * 100;
	int delta = 0;
	if (c <= 33) {
		delta = -1;
	} else if (c >= 67) {
		delta = 1;
	}
	int new_rep = Seeker_Rep + delta;
	new_rep = std::min(5, new_rep);
	new_rep = std::max(1, new_rep);
	Seeker_Rep = new_rep;
}

void HRC::match() {
	s_p_Worker placedWorker;
	for (list<s_p_Job>::iterator it = openings.begin(); it != openings.end(); ++it) {
		if (matchForJob(*it, placedWorker)) {
			candidate_placement(placedWorker, *it);
		}
	}

}
void HRC::candidate_placement(s_p_Worker placedWorker, s_p_Job job) {
//	placedWorker->setOutDate();
	placedWorker->hired();
	job->taken(time);
	monthly_placements++;
	seekers.remove(placedWorker);
	openings.remove(job);
	float salary = placedWorker->getExpectedSalary();
	Poco::DateTime outDate = time;
	int jobType = ((companies.find(job->CompanySN))->second)->type;
	Placement p;
	p.salary = salary;
	p.outDate = time;
	p.job = job;
	p.job_type = jobType;
	p.worker = placedWorker;
	for (int i = 0; i < 6; ++i) {
		if (job->skills[i]) {
			placementsBySkillType[i].insert(p); // insert Placement p by SkillType
		}
	}
	placementsByJobType[jobType].insert(p);
	placementsByDate.insert(p);

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
	if (applicants.size() > 0 && screenApplicants(jobPtr, applicants,
			choosenOne)) {
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
		int skills[6];
		worker.getSkills(skills);
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
	if (strategy == 1) {
		return applicants;
	} else { //strategy == FAIR
		float tot = 0;
		float num = 0;
		for (v_p_Worker::iterator it = applicants.begin(); it
				!= applicants.end(); ++it) {
			tot += (time - (*it)->getInDate()).days();
			num += 1;
		}
		float avg = tot / num;
		for (v_p_Worker::iterator it = applicants.begin(); it
				!= applicants.end(); ++it) {
			if ((time - (*it)->getInDate()).days() < avg) {
				it = applicants.erase(it);
			}
		}
		return applicants;
	}
}

bool HRC::screenApplicants(s_p_Job jobPtr, vector<s_p_Worker> applicants,
		s_p_Worker choosenOne) {
	// get company and company strategy
	int companySN = jobPtr->CompanySN;
	s_p_Company companyPtr = companies.find(companySN)->second;
	int recruitingPolicy = companyPtr->getRecruitingPolicy();
	if (recruitingPolicy == CHEAP)
		return screenApplicantsCheap(jobPtr, applicants, choosenOne);
	else if (recruitingPolicy == LAVISH)
		return screenApplicantsLavish(jobPtr, applicants, choosenOne);
	else
		// recruitingPolicy == COST_EFFECTIVE
		return screenApplicantsCostEffective(jobPtr, applicants, choosenOne);
}

bool HRC::screenApplicantsCheap(s_p_Job jobPtr, vector<s_p_Worker> applicants,
		s_p_Worker choosenOne) {
	bool found = false;
	float minQL = ((companies.find(jobPtr->CompanySN))->second)->QL_Min;
	//	s_p_Worker choosenOne;// = *applicants.begin();
	int curMin = std::numeric_limits<int>::max();
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		int tmp = (*it)->getExpectedSalary();
		float tmpQL = QL(*it, jobPtr);
		if (tmp < curMin && tmpQL >= minQL) {
			curMin = tmp;
			choosenOne = *it;
			found = true;
		} else if (tmpQL >= minQL && tmp == curMin && ((*it)->getID()
				< choosenOne->getID())) {
			curMin = tmp;
			choosenOne = *it;
			found = true;
		}
	}
	return found;
}

bool HRC::screenApplicantsLavish(s_p_Job jobPtr, vector<s_p_Worker> applicants,
		s_p_Worker choosenOne) {
	//	s_p_Worker choosenOne = *applicants.begin();
	bool found = false;
	float minQL = ((companies.find(jobPtr->CompanySN))->second)->QL_Min;
	float curBest = 0;
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		double tmp = QL(*it, jobPtr);
		if (tmp > curBest && tmp >= minQL) {
			curBest = tmp;
			choosenOne = *it;
			found = true;
		} else if (tmp >= minQL && tmp == curBest && ((*it)->getID()
				< choosenOne->getID())) {
			curBest = tmp;
			choosenOne = *it;
			found = true;
		}
	}
	return found;
}

bool HRC::screenApplicantsCostEffective(s_p_Job jobPtr,
		vector<s_p_Worker> applicants, s_p_Worker choosenOne) {
	//	s_p_Worker choosenOne = *applicants.begin();
	bool found = false;
	float minQL = ((companies.find(jobPtr->CompanySN))->second)->QL_Min;
	float curBest = 0;//(QL(choosenOne, *jobPtr))
	//			/ choosenOne->getExpectedSalary();
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		float tmpQL = (QL(*it, jobPtr));
		float tmp = tmpQL / (*it)->getExpectedSalary();
		if (tmp > curBest && tmpQL >= minQL) {
			curBest = tmp;
			choosenOne = *it;
			found = true;
		} else if (tmpQL >= minQL && tmp == curBest && ((*it)->getID()
				< choosenOne->getID())) {
			curBest = tmp;
			choosenOne = *it;
			found = true;
		}
	}
	return found;
}

//bool HRC::compareSalaries(s_p_Worker* w1, s_p_Worker* w2) {
//	return ((*w1)->getExpectedSalary()) < ((*w2)->getExpectedSalary());
//}

float HRC::QL(s_p_Worker worker, s_p_Job job) {
	int skills[6];
	worker->getSkills(skills);
	float tot(0);
	float num(0);
	for (int j = 0; j < 6; ++j) {
		if (job->skills[j]) {
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

std::string HRC::job_type_stringer(bool types[]) {
	std::string s;
	for (int i = 0; i < 6; ++i) {
		if (types[i]) {
			s = s + int2EJobType(i) + " ";
		}
	}
	return s;
}

void HRC::reportJobOpening(int SN, DT date) {
	s_p_Job job = (jobs.find(SN))->second;
	ass2::JobType job_type;
	long int days = job->comp_days(date);
	bool closed = job->closed;
	job_type = ass2::JobType(int2EJobType(job->type));
	reporter.reportJobOpening(SN, job_type, days, closed, date);
}

void HRC::reportCandidate(int ID, DT date) {
	s_p_Worker worker = workers.find(ID)->second;
	bool types[6];
	worker->getDesiredJobTypes(types);
	string job_types = job_type_stringer(types);
	int days = worker->comp_days();
	bool found_job = worker->isOccupied();
	reporter.reportCandidate(ID, job_types, days, found_job, date);
}



Poco::DateTime HRC::string_dater(std::string in_str) {
	std::vector<std::string> strs;
	boost::split(strs, in_str, boost::is_any_of("\\"));
	Poco::DateTime ret(boost::lexical_cast<int>(strs[2]), boost::lexical_cast<
			int>(strs[1]), boost::lexical_cast<int>(strs[0]));
	return ret;

}
std::string HRC::int2EJobType(int type) {
	switch (type) {
	case 0:
		return "data_storage";
	case 1:
		return "digital_media";
	case 2:
		return "e_commerce";
	case 3:
		return "gaming";
	case 4:
		return "rt";
	case 5:
		return "security";
	default:
		return "";
	}
}

std::string HRC::int2ESkillType(int skill) {
	switch (skill) {
	case 0:
		return "cpp";
	case 1:
		return "java";
	case 2:
		return "script";
	case 3:
		return "web";
	case 4:
		return "system";
	case 5:
		return "qa";
	default:
		return "";
	}
}

