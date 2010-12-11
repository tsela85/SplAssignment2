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
//#include <memory>
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"
#include "../include/Worker.h"
#include "../include/Job.h"
#include "../include/Company.h"
#include "../include/JobType.h"
#include "../include/SkillType.h"
//#include "../include/Placement.h"
#include <boost/ptr_container/ptr_list.hpp>
#include "../include/defs.h"
#include "../include/HRCReport.h"

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
  bool operator() (Placement lhs, Placement rhs) const
  {return lhs.worker->getOutDate() < rhs.worker->getOutDate();}
};



class HRC {
private:
	std::map<int, s_p_Worker> workers;
	std::map<int, s_p_Job> jobs;
	std::map<int, s_p_Company> companies;
	std::list<s_p_Worker> seekers;
	std::list<s_p_Job> openings;
	long profit;
	Poco::DateTime time;
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

public:

	HRC();

	HRC(Poco::DateTime sDate, int _Seeker_rep, int _Company_rep, int strategy);

	void setDate(Poco::DateTime newDate);

	void incDate();

	void addCandidate(s_p_Worker w);

	void addJob(s_p_Job j);

	int getStrategy() {
		return strategy;
	}

	void setStrategy(int s) {
		strategy = s;
	}

	void update_Company_Rep();

	void update_Seeker_Rep();

	void match();

	bool matchForJob(s_p_Job jobPtr, s_p_Worker workerPtr);

	void candidate_placement(s_p_Worker placedWorker, s_p_Job job);

	void copySkills(vector<bool> skills, int size, Worker worker);

	vector<s_p_Worker> getApplicants(s_p_Job jobPtr);

	bool screenApplicants(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker choosenOne);

	bool screenApplicantsCheap(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker choosenOne);

	bool screenApplicantsLavish(s_p_Job jobPtr, vector<s_p_Worker> applicants,
			s_p_Worker choosenOne);

	bool screenApplicantsCostEffective(s_p_Job jobPtr,
			vector<s_p_Worker> applicants, s_p_Worker choosenOne);

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

	void reportSalarySurvey(const ass2::SkillType* skill, DT sDate, DT eDate);

	void reportSalarySurvey(const ass2::SkillType* skill, string sDate, string eDate) {
		reportSalarySurvey(skill, string_dater(sDate), string_dater(eDate));
	}

	void reportProfit(DT sDate, DT eDate);

	void reportProfit(string sDate, string eDate){
		reportProfit(string_dater(sDate), string_dater(eDate));
	}


};



#endif /* HRC_H_ */
