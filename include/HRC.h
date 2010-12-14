/*
 * HRC.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */

#ifndef HRC_H_
#define HRC_H_

#include <map>
#include <set>
#include <vector>
#include <list>
//#include <memory>
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"
#include "../include/Worker.h"
#include "../include/Job.h"
#include "../include/Company.h"
#include "../include/JobType.h"
#include "../include/SkillType.h"
#include "../include/Command.h"
//#include "../include/Placement.h"
#include <boost/ptr_container/ptr_list.hpp>
#include "../include/defs.h"
#include "../include/HRCReport.h"
#include "../include/AppLogger.h"

typedef boost::shared_ptr<Company> s_p_Company;
typedef Poco::DateTime DT;

struct Placement {
	s_p_Job job;
	s_p_Worker worker;
	float salary;
	int job_type;
	Poco::DateTime outDate;

};

struct classcomp {//to order the set by Poco::DateTime
	bool operator()(Placement lhs, Placement rhs) const {
		return lhs.worker->getOutDate() < rhs.worker->getOutDate();
	}
};

struct comp_date_sn_jobs {
	bool operator()(s_p_Job j1, s_p_Job j2) const {
		if (j1->inDate < j2->inDate)
			return true;
		else if (j1->inDate == j2->inDate)
			return (j1->SN) < (j2->SN);
		else
			return false;
	}
};

//struct comp_date_worker {//to order the set by Poco::DateTime
//	bool /*operator()*/ comp_date_worker(s_p_Worker lhs, s_p_Worker rhs) /*const*/ { //FIXME: fix sort
//		return lhs->getInDate() < rhs->getInDate() /*true*/;
//	}
//};

class HRC {
	/*bool comp_date_worker(s_p_Worker lhs, s_p_Worker rhs) { //FIXME: fix sort
			return lhs->getInDate() < rhs->getInDate() true;
	}*/
private:
	std::map<int, s_p_Worker> workers;
	std::map<int, s_p_Job> jobs;
	std::map<int, s_p_Company> companies;
	list<s_p_Worker> seekers;
	set<s_p_Job, comp_date_sn_jobs> openings;
	long profit;
	Poco::DateTime *time;
	int Company_Rep;
	int Seeker_Rep;
	int strategy;
	vector<set<Placement, classcomp> > placementsBySkillType;
	vector<set<Placement, classcomp> > placementsByJobType;
	set<Placement, classcomp> placementsByDate;
	int monthly_candidates;
	int monthly_jobs;
	int monthly_placements;
	std::string Aviad;
	std::string Tom;
	HRCReport reporter;
	CAppLogger *logger;
	bool terminate;
public:

	HRC();

	HRC(Poco::DateTime *sDate, int _Seeker_rep, int _Company_rep, int strategy,
			CAppLogger *logger);

	void setDate(Poco::DateTime newDate);

	void incDate();

	void addCandidate(s_p_Worker w);

	void addJob(s_p_Job j);

	void addCompany(s_p_Company c);

	int getStrategy() {
		return strategy;
	}

	void setStrategy(int s) {
		strategy = s;
	}

	void update_Company_Rep();

	void update_Seeker_Rep();

	void match();

	bool matchForJob(s_p_Job jobPtr, s_p_Worker *workerPtr);

	void candidate_placement(s_p_Worker placedWorker, s_p_Job job);

	void copySkills(vector<bool> skills, int size, Worker worker);

	vector<s_p_Worker> getApplicants(s_p_Job jobPtr);

	bool screenApplicants(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker *choosenOne);

	bool screenApplicantsCheap(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker *choosenOne);

	bool screenApplicantsLavish(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker *choosenOne);

	bool screenApplicantsCostEffective(s_p_Job jobPtr,
			vector<s_p_Worker> applicants, s_p_Worker *choosenOne);

	bool compareSalaries(s_p_Worker* w1, s_p_Worker* w2);

	float QL(s_p_Worker worker, s_p_Job job);

	std::string job_type_stringer(bool types[]);

	Poco::DateTime string_dater(std::string s);

	std::string int2EJobType(int type);

	std::string int2ESkillType(int type);

	void reportCandidate(int ID, Poco::DateTime date);

	void reportCandidate(int ID, string date) {
		reportCandidate(ID, string_dater(date));
	}

	void reportJobOpening(int SN, DT date);

	void reportJobOpening(int SN, string date) {
		reportJobOpening(SN, string_dater(date));
	}

	void reportSalarySurvey(ass2::JobType job_type, DT sDate, DT eDate);

	void reportSalarySurvey(ass2::JobType job_type, string sDate, string eDate) {
		reportSalarySurvey(job_type, string_dater(sDate), string_dater(eDate));
	}

	void reportSalarySurvey(SkillType skill, DT sDate, DT eDate);

	void reportSalarySurvey(SkillType skill, string sDate,
			string eDate) {
		reportSalarySurvey(skill, string_dater(sDate), string_dater(eDate));
	}

	void reportProfit(DT sDate, DT eDate);

	void reportProfit(string sDate, string eDate) {
		reportProfit(string_dater(sDate), string_dater(eDate));
	}

	int get_seeker_rep() {
		return Seeker_Rep;
	}

	int get_company_rep() {
		return Company_Rep;
	}

	bool getTerminate() {
		return terminate;
	}

	void terminateProgram() {
		terminate=true;
	}

	void compromise();

	bool is_last_day();

	void ourReport();


};

#endif /* HRC_H_ */
