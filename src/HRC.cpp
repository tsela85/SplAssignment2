/*
 * HRC.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: Tom and Aviad
 */

#include "../include/HRC.h"
#include <algorithm>
#include <limits>
#include <iostream>
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
	terminate = false;
	//	reporter(std::string("052978509"), std::string("37054244"));
}

HRC::HRC(Poco::DateTime *sDate, int _Seeker_rep, int _Company_rep,
		int _strategy, CAppLogger *_logger) {
	//	HRC();
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
	time = sDate;
	Seeker_Rep = _Seeker_rep;
	Company_Rep = _Company_rep;
	strategy = _strategy;
	logger = _logger;
	terminate = false;
}

void HRC::setDate(Poco::DateTime newDate) {
	*time = newDate;
}

/**
 * increment time by 1 day.
 */
void HRC::incDate() {
	*time += Poco::Timespan(1, 0, 0, 0, 0);
	ostringstream msg;
	msg << "date was changed to " << time->day() << "/" << time->month() << "/"
			<< time->year() << endl;
	logger->Log(msg.str(), Poco::Message::PRIO_TRACE);
}

void HRC::addCandidate(s_p_Worker w) {
	w->setInDate();
	//	s_p_Worker workerPtr(new Worker(w));
	workers.insert(std::make_pair(w->getID(), w));
	seekers.push_back(w);
	monthly_candidates++;
	ostringstream msg;
	msg << "Candidate " << w->getID() << " was added to the HRC DB.";
	logger->Log(msg.str(), Poco::Message::PRIO_WARNING);
	ostringstream msg2;
	msg2 << "No of seekers in DB: " << seekers.size()
			<< "\tand in 'workers' map: " << workers.size();
	logger->Log(msg2.str(), Poco::Message::PRIO_TRACE);
}

void HRC::addJob(s_p_Job j) {
	//	s_p_Job jobPtr(new Job(j));
	j->setInDate(time);
	int type((companies.find(j->CompanySN))->second->getType());
	j->setType(type);
	jobs.insert(std::make_pair(j->SN, j));
	openings.insert(j);
	monthly_jobs++;
	ostringstream msg;
	msg << "Job Opening " << j->SN << " was added to the HRC DB.";
	logger->Log(msg.str(), Poco::Message::PRIO_WARNING);
}

void HRC::addCompany(s_p_Company c) {
	companies.insert(make_pair(c->getSN(), c));
	ostringstream msg;
	int temp = c->getSN();
	msg << "Company " << temp << " was added to the HRC DB.";
	logger->Log(msg.str(), Poco::Message::PRIO_WARNING);
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
	ostringstream msg;
	msg << "Employer Reputation was updated to " << new_rep << ".";
	logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
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
	ostringstream msg;
	msg << "Job Seeker Reputation was updated to " << new_rep << ".";
	logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
}

void HRC::match() {
	s_p_Worker placedWorker;
	for (set<s_p_Job, comp_date_sn_jobs>::iterator it = openings.begin(); it
			!= openings.end();) {
		if (matchForJob(*it, &placedWorker)) {
			candidate_placement(placedWorker, *it);

			ostringstream msg11;
			msg11 << "Jobs before deleting.. no of jobs " << openings.size()
					<< endl;
			logger->Log(msg11.str(), Poco::Message::PRIO_TRACE);

			openings.erase(it++);

			ostringstream msg21;
			msg21 << "Jobs after deleting.. no of jobs " << openings.size() << endl;
			logger->Log(msg21.str(), Poco::Message::PRIO_TRACE);

			ostringstream msg1;
			msg1 << "before deleting.. no of seekers " << seekers.size()
					<< endl;
			logger->Log(msg1.str(), Poco::Message::PRIO_TRACE);
			//	map<s_p_Worker, comp_date_worker>iterator debug = seekers.find(placedWorker);
			seekers.remove(placedWorker);

			ostringstream msg2;
			msg2 << "after deleting.. no of seekers " << seekers.size() << endl;
			logger->Log(msg2.str(), Poco::Message::PRIO_TRACE);
		} else
			++it;
	}

}
void HRC::candidate_placement(s_p_Worker placedWorker, s_p_Job job) {
	//	placedWorker->setOutDate();
	placedWorker->hired();
	job->taken(*time);
	monthly_placements++;

	//	openings.erase(job);
	float salary = placedWorker->getExpectedSalary();
	Poco::DateTime outDate = *time;
	int jobType = ((companies.find(job->CompanySN))->second)->type;
	Placement p;
	p.salary = salary;
	p.outDate = *time;
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
	ostringstream msg;
	msg << "Candidate " << placedWorker->getID()
			<< " was accepted to job opening " << job->SN << " at "
			<< ((companies.find(job->CompanySN))->second)->getName() << ".";
	logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
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

bool HRC::matchForJob(s_p_Job jobPtr, s_p_Worker *choosenOne) {
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
	for (list<s_p_Worker/*, comp_date_worker*/>::iterator it = seekers.begin(); it
			!= seekers.end(); ++it) {
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
			tot += (*time - (*it)->getInDate()).days();
			num += 1;
		}
		float avg = tot / num;
		for (v_p_Worker::iterator it = applicants.begin(); it
				!= applicants.end();) {
			if ((*time - (*it)->getInDate()).days() < avg) {
				applicants.erase(it++);
			} else {
				++it;
			}
		}
		return applicants;
	}
}

bool HRC::screenApplicants(s_p_Job jobPtr, vector<s_p_Worker> applicants,
		s_p_Worker *choosenOne) {
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
		s_p_Worker *choosenOne) {
	bool found = false;
	float minQL = ((companies.find(jobPtr->CompanySN))->second)->QL_Min;
	//	s_p_Worker choosenOne;// = *applicants.begin();
	int curMin = std::numeric_limits<int>::max();
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		ostringstream msg;
		msg << "Candidate " << (*it)->getID()
				<< " was notified about job opening " << jobPtr->SN << ".";
		logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
		int tmp = (*it)->getExpectedSalary();
		float tmpQL = QL(*it, jobPtr);
		if (tmp < curMin && tmpQL >= minQL) {
			curMin = tmp;
			*choosenOne = *it;
			found = true;
		} else if (tmpQL >= minQL && tmp == curMin && ((*it)->getID()
				< (*choosenOne)->getID())) {
			curMin = tmp;
			*choosenOne = *it;
			found = true;
		}
	}
	return found;
}

bool HRC::screenApplicantsLavish(s_p_Job jobPtr, vector<s_p_Worker> applicants,
		s_p_Worker *choosenOne) {
	//	s_p_Worker choosenOne = *applicants.begin();
	bool found = false;
	float minQL = ((companies.find(jobPtr->CompanySN))->second)->QL_Min;
	float curBest = 0;
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		ostringstream msg;
		msg << "Candidate " << (*it)->getID()
				<< " was notified about job opening " << jobPtr->SN << ".";
		logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
		double tmp = QL(*it, jobPtr);
		if (tmp > curBest && tmp >= minQL) {
			curBest = tmp;
			*choosenOne = *it;
			found = true;
		} else if (tmp >= minQL && tmp == curBest && ((*it)->getID()
				< (*choosenOne)->getID())) {
			curBest = tmp;
			*choosenOne = *it;
			found = true;
		}
	}
	return found;
}

bool HRC::screenApplicantsCostEffective(s_p_Job jobPtr,
		vector<s_p_Worker> applicants, s_p_Worker *choosenOne) {
	//	s_p_Worker choosenOne = *applicants.begin();
	bool found = false;
	float minQL = ((companies.find(jobPtr->CompanySN))->second)->QL_Min;
	float curBest = 0;//(QL(choosenOne, *jobPtr))
	//			/ choosenOne->getExpectedSalary();
	for (vector<s_p_Worker>::iterator it = applicants.begin(); it
			!= applicants.end(); ++it) {
		ostringstream msg;
		msg << "Candidate " << (*it)->getID()
				<< " was notified about job opening " << jobPtr->SN << ".";
		logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
		float tmpQL = (QL(*it, jobPtr));
		float tmp = tmpQL / (*it)->getExpectedSalary();
		if (tmp > curBest && tmpQL >= minQL) {
			curBest = tmp;
			*choosenOne = *it;
			found = true;
		} else if (tmpQL >= minQL && tmp == curBest && ((*it)->getID()
				< (*choosenOne)->getID())) {
			curBest = tmp;
			*choosenOne = *it;
			found = true;
		}
	}
	return found;
}

void HRC::compromise() {
	bool go_on = true;
	for (list<s_p_Worker/*, comp_date_worker*/>::iterator it = seekers.begin(); it
			!= seekers.end() && go_on; it++) {
		go_on = (*it)->compromise();
	}
}

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
	size_t next_to_last = s.length() - 1;
	return s.substr(0, next_to_last);
}

void HRC::reportJobOpening(int SN, DT date) {
	map<int, s_p_Job>::iterator jobs_iter = jobs.find(SN);//->second;
	if (jobs_iter == jobs.end()) {
		std::cout << "no job with SN " << SN << endl;
		return;
	}
	s_p_Job job = jobs_iter->second;
	ass2::JobType job_type;
	long int days = job->comp_days(date);
	bool closed = job->closed;
	job_type = ass2::JobType(int2EJobType(job->type));
	reporter.reportJobOpening(SN, job_type, days, closed, date);
	ostringstream msg;
	msg << "Job Opening report was generated.";
	logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
}

void HRC::reportCandidate(int ID, DT date) {
	map<int, s_p_Worker>::iterator worker_iter = workers.find(ID);//->second;
	if (worker_iter == workers.end()) {
		std::cout << "no candidate with ID " << ID << endl;
		return;
	}
	s_p_Worker worker = worker_iter->second;
	bool types[6];
	worker->getDesiredJobTypes(types);
	string job_types = job_type_stringer(types);
	int days = worker->comp_days();
	bool found_job = worker->isOccupied();
	reporter.reportCandidate(ID, job_types, days, found_job, date);
	ostringstream msg;
	msg << "Candidate report was generated.";
	logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
}

void HRC::reportProfit(DT sDate, DT eDate) {
	long profit = 0;
	for (set<Placement, classcomp>::iterator it = placementsByDate.begin(); it
			!= placementsByDate.end() && ((it->outDate) <= eDate); ++it) {
		if (it->outDate >= sDate) {
			profit += it->salary;
		}
	}
	reporter.reportProfit(profit, sDate, eDate);
	ostringstream msg;
	msg << "Profit report was generated.";
	logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
}

void HRC::reportSalarySurvey(JobType job_type, DT sDate, DT eDate) {
	double avg_salary = 0, tot_salaries = 0;
	int n = 0;
	set<Placement, classcomp> db_set = placementsByJobType[job_type.to_num()];
	for (set<Placement, classcomp>::iterator it = db_set.begin(); it
			!= db_set.end(); it++) {
		tot_salaries += it->salary;
		n++;
	}
	avg_salary = tot_salaries / n;
	reporter.reportSalarySurvey(job_type, avg_salary, sDate, eDate);
	ostringstream msg;
	msg << "Salary Survey report was generated.";
	logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
}

void HRC::reportSalarySurvey(SkillType skill, DT sDate, DT eDate) {
	double avg_salary = 0, tot_salaries = 0;
	int n = 0;
	set<Placement, classcomp> db_set = placementsBySkillType[skill.to_num()];
	for (set<Placement, classcomp>::iterator it = db_set.begin(); it
			!= db_set.end(); it++) {
		tot_salaries += it->salary;
		n++;
	}
	avg_salary = tot_salaries / n;
	reporter.reportSalarySurvey(&skill, avg_salary, sDate, eDate);
	ostringstream msg;
	msg << "Salary Survey report was generated.";
	logger->Log(msg.str(), Poco::Message::PRIO_NOTICE);
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

bool HRC::is_last_day() {
	DT today = *time;
	DT tomorrow = *time + Poco::Timespan(1, 0, 0, 0, 0);
	return tomorrow.month() != today.month();
}

void HRC::ourReport() {
	ostringstream msg;
	msg << "Total number of Candidates in the DB: " << seekers.size() << endl
			<< "Total number of Job openings in the DB: " << openings.size();
	logger->Log(msg.str(), Poco::Message::PRIO_TRACE);
}
