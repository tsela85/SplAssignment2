#include "HRCReport.h"
#include <iostream>
#include <iomanip>

	using std::string;
	using Poco::DateTime;

	HRCReport::HRCReport(){}

	HRCReport::HRCReport(string firstId,  string secondId)
		: m_FirstId(firstId),m_SecondId(secondId){}
	
	HRCReport::~HRCReport(){}


	void HRCReport::reportCandidate(int id, string job_types,long days,
			bool found_job,	string date) const
	{
		string found_job_str = (found_job? "YES":"NO");
		std::cout <<  std::endl << "***Candidate Report***" << std::endl <<
			date << std::endl <<
			"ID: " << id << std::endl <<
			"Days in the HR Centre DB: " << days << std::endl <<
			"Found a Job: " << found_job_str << std::endl;
	}

	void HRCReport::reportCandidate(int id, string job_types, long days,
			bool found_job,	const Poco::DateTime & date) const{
			reportCandidate(id, job_types, days, found_job, toStr(date));
	}
	
	void HRCReport::reportJobOpening(int sn, JobType job_type, long days,
			bool job_closed, string date) const
	{
		string Job_Opening_Closed = (job_closed? "YES":"NO");
		std::cout <<  std::endl << "***Job Opening Report***" << std::endl <<
			date << std::endl <<
			"SN: " << sn << std::endl <<
			"Job Type: " << job_type << '\n' <<
			"Days in the HR Centre DB: " << days << std::endl <<
			"Job Opening Closed: " << Job_Opening_Closed << std::endl;
	}

	void HRCReport::reportJobOpening(int sn, JobType job_type, long days,
			bool job_closed, const Poco::DateTime & date) const{
				reportJobOpening(sn, job_type, days, job_closed, toStr(date));
	}


	//Reports salary survey of a certain job_type. Use time parameter as a string (day/month/year)
	void HRCReport::reportSalarySurvey(JobType job_type, double average_salary,
			string sDate, string eDate) const
	{
		std::cout <<  std::endl << "***Salary Survey Report***" << std::endl <<
			sDate << " - "<< eDate << std::endl <<
			"Job Type: " << job_type << std::endl <<
			"Average Salary: " << std::fixed << std::setprecision(1) <<
			average_salary << std::endl;
	}

	//Reports salary survey of a certain job_type. Use as a DateTime
	void HRCReport::reportSalarySurvey(JobType job_type, double average_salary,
			const Poco::DateTime & sDate, const Poco::DateTime& eDate) const
	{
		reportSalarySurvey(job_type, average_salary, toStr(sDate), toStr(eDate));
	}

	//Reports salary survey of a certain job_type. Use time parameter as a string (day/month/year)
	void HRCReport::reportSalarySurvey(const SkillType* skill, double average_salary,
			string sDate, string eDate) const
	{
		std::cout <<  std::endl << "***Salary Survey Report***" << std::endl <<
			sDate << " - "<< eDate << std::endl <<
			"Programming skill: " << *skill << std::endl <<
			"Average Salary: " << std::fixed << std::setprecision(1) <<
			average_salary << std::endl;
	}

	//Reports salary survey of a certain job_type. Use as a DateTime
	void HRCReport::reportSalarySurvey(const SkillType* skill, double average_salary,
			const Poco::DateTime & sDate, const Poco::DateTime& eDate) const
	{
		reportSalarySurvey(skill, average_salary, toStr(sDate), toStr(eDate));
	}

	void HRCReport::reportProfit(long profit, string sDate, string eDate) const
	{
		std::cout << "***Profit Report***" << '\n' <<
		sDate << " - " << eDate  << '\n' <<
		"Profit: " << profit << " NIS." << std::endl ;
	}

	void HRCReport::reportProfit(long profit, const DateTime& sDate,
			const DateTime& eDate) const{
		reportProfit(profit, toStr(sDate), toStr(eDate));
	}

	string HRCReport::toStr(const Poco::DateTime& date) const{
            std::ostringstream ostr;
			string sDate;
			ostr << date.day() << "/" << date.month() << "/" << date.year();
			sDate = ostr.str();
			return sDate;
	}
	
