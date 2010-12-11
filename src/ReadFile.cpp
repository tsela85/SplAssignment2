// ReadFile.cpp

#include <sstream>

#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "../include/ReadFile.h"
#include "../h/AppLogger.h"

using namespace Poco;
using namespace Poco::Util;
using namespace std;

int switchToInt(string temp);

// Constructor that receive data stream as std::istream
ReadFile::ReadFile(std::istream& istr) : IniFileConfiguration(istr) {

}

// Constructor that receive path as std::string
ReadFile::ReadFile(const std::string& path) : IniFileConfiguration(path){
}

ReadFile::~ReadFile(){
}

void ReadFile::getConfig(Poco::DateTime *_date, int *_jobNum, int *_workNum,int *_seekerRep
		,int *_companyRep,int *_HrcStrat,int *_logConP,int *_logFileP) {

	ostringstream streamDate;
	ostringstream streamJobNum;
	ostringstream streamWorkNum;
	ostringstream streamSeekerRep;
	ostringstream streamCompanyRep;
	ostringstream streamHrcStrat;
	ostringstream streamLogConp;
	ostringstream streamLogFileP;

	// Get  INITIAL_DATE
	streamDate << "GENERAL.INITIAL_DATE";
	string dateStr =
			getString(streamDate.str());
	int timeZoneDiff;
	DateTime date;
	DateTimeParser::tryParse("%d/%n/%Y", dateStr, date, timeZoneDiff);
	*_date=date;

	// Get job number
	streamJobNum << "GENERAL.INIT_JOBS_NUM";
	*_jobNum = getInt(streamJobNum.str());

	// Get work number
	streamWorkNum << "GENERAL.INIT_CANDS_NUM";
	*_workNum = getInt(streamWorkNum.str());

	// Get seeker rep
	streamSeekerRep << "GENERAL.INIT_SEEKER_REP";
	*_seekerRep = getInt(streamSeekerRep.str());

	// Get company rep
	streamCompanyRep << "GENERAL.INIT_COMPANY_REP";
	*_companyRep = getInt(streamCompanyRep.str());

	// Get HRC strategy
	streamHrcStrat << "GENERAL.HRC_STRATEGY";
	string stratString=getString(streamHrcStrat.str());
	if (stratString == "EAGER")
		*_HrcStrat = EAGER;
	else
		if (stratString == "FAIR")
			*_HrcStrat = FAIR;
	//   else TODO: throw exception error reading

	// Get LOGGER_CONSOLE_PRIORITY
	streamLogConp << "GENERAL.LOGGER_CONSOLE_PRIORITY";
	*_logConP = getInt(streamLogConp.str());

	// Get LOGGER_FILE_PRIORITY
	streamLogFileP << "GENERAL.LOGGER_FILE_PRIORITY";
	*_logFileP = getInt(streamLogFileP.str());
}

int ReadFile::getWorkers(std::vector<s_p_Worker> *_workers) {
	ostringstream sAmount;
	sAmount << "numberOfCANDIDATES";
	int amount = getInt(sAmount.str());
	for (int i=1; i <= amount; i++) {
		// ID
		ostringstream sID;
		sID << "CANDIDATE" << i << ".ID";
		int ID = boost::lexical_cast<int>(getString(sID.str()));
		// Skills
		ostringstream sSkillNum;
		sSkillNum << "CANDIDATE" << i << ".numberOfSkills";
		int skillNum = getInt(sSkillNum.str());
		int skills[6];
		for(int k=0;k < 6;k++) skills[k]=0;
		for(int j=1; j <= skillNum;j++) {
			ostringstream sSkill;
			sSkill << "CANDIDATE" << i << ".Skill" << j;
			string skill= getString(sSkill.str());
			vector<string> parts;
			boost::algorithm::split(parts,skill,boost::is_any_of(" "));
			skills[switchToInt(parts[0])]=boost::lexical_cast<int>(parts[1]);
		}
		// Expected_Salary
		ostringstream sSalary;
		sSalary << "CANDIDATE" << i << ".Expected_Salary";
		float salary = getDouble(sSalary.str());
		// Desired_Job_Type
		bool jobs[6];
		for(int k=0;k < 6;k++) jobs[k]=false;
		ostringstream sjobs;
		sjobs << "CANDIDATE" << i << ".Desired_Job_Type";
		string job= getString(sjobs.str());
		vector<string> parts;
		boost::algorithm::split(parts,job,boost::is_any_of(" "));
		for (vector<string>::iterator it = parts.begin(); it != parts.end(); it++)
			jobs[switchToInt(*it)]=true;
		// create a worker
		s_p_Worker worker(new Worker(ID,skills,jobs,salary,time,logger));
		_workers->push_back(worker);
	}

	return amount;
}

int ReadFile::getCompanies(std::vector<s_p_Company> *_companies) {
	ostringstream sAmount;
	sAmount << "numberOfCompanies";
	int amount = getInt(sAmount.str());
	for (int i=1; i <= amount; i++) {
		// ID
		ostringstream sSN;
		sSN << "COMPANY" << i << ".SN";
		int SN = boost::lexical_cast<int>(getString(sSN.str()));
		// Name
		ostringstream sName;
		sName << "COMPANY" << i << ".Name";
		string name = getString(sName.str());
		// CompanyType
		ostringstream sType;
		sType << "COMPANY" << i << ".CompanyType";
		int type = switchToInt(getString(sType.str()));
		// RecruitingPolicy
		ostringstream sRecPolicy;
		sRecPolicy << "COMPANY" << i << ".RecruitingPolicy";
		int recPolicy = switchToInt(getString(sRecPolicy.str()));
		// QL_Min
		ostringstream sQl;
		sQl << "COMPANY" << i << ".QL_Min ";
		float ql = getDouble(sQl.str());

		// create a company
		s_p_Company company(new Company(name,type,SN,recPolicy,ql));
		_companies->push_back(company);
	}

	return amount;
}

int ReadFile::getJobs(std::vector<s_p_Job> *_jobs) {
	ostringstream sAmount;
	sAmount << "numberOfJOBS";
	int amount = getInt(sAmount.str());

	for (int i=1; i <= amount; i++) {
		// ID
		ostringstream sID;
		sID << "JOB" << i << ".ID";
		int ID = boost::lexical_cast<int>(getString(sID.str()));

		// Skills
		ostringstream sSkillNum;
		sSkillNum << "JOB" << i << ".numberOfSkills";
		int skillNum = getInt(sSkillNum.str());
		bool skills[6];
		for(int k=0;k < 6;k++) skills[k]=false;
		for(int j=1; j <= skillNum;j++) {
			ostringstream sSkill;
			sSkill << "JOB" << i << ".Skill" << j;
			string skill= getString(sSkill.str());
			skills[switchToInt(skill)]=true;
		}
		// CompanySN
		ostringstream sSN;
		sSN << "JOB" << i << ".CompanySN";
		int SN = boost::lexical_cast<int>(getString(sSN.str()));

		// create a job

		s_p_Job job(new Job(ID,skills,SN,time));
		_jobs->push_back(job);
	}

	return amount;

}


int switchToInt(string temp) {
	// temp=stl::tolower(temp); TODO: switch to lower case
	if (temp == "cpp") return _CPP;
	if (temp == "java") return _JAVA;
	if (temp == "script") return _SCRIPT;
	if (temp == "web") return _WEB;
	if (temp == "system") return _SYSTEM;
	if (temp == "qa") return _QA;

	if (temp == "data_storage") return _DATA_STORAGE;
	if (temp == "digital_media") return _DIGITAL_MEDIA;
	if (temp == "e_commerce") return _E_COMMERCE ;
	if (temp == "gaming") return _GAMING;
	if (temp == "rt") return _RT;
	if (temp == "security") return _SECURITY;

	if (temp == "Cheap") return CHEAP;
	if (temp == "Lavish") return LAVISH;
	if (temp == "Cost_Effective") return COST_EFFECTIVE;

	return -1; // TODO: throw error
}

