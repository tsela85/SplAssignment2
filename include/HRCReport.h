//SPL 2011
//Assignment 2
//Last change 26/11/10

#ifndef HRCReport_H
#define HRCReport_H

#include "JobType.h"
#include "SkillType.h"

#include "Poco/DateTime.h"

#include <string>
#include <vector>
#include <sstream>

using namespace ass2;
/*
 * Class CMarketReport generates the reports event for assignment 2. 
 * The structure and enum were defined in commonDef.h file.
 * The user is responsible to allocate and release the memory.
 * note that some functions use reference and other pointer.
 * all report return true if the report execute.
 */

class HRCReport
{
public:

 	//constructor
	HRCReport();

	//constructor parameters:
	//firstId and secondId - your id (for grading the assignment).
	HRCReport(std::string firstId, std::string secondId);
	
	
	virtual ~HRCReport();
    

    //Reports candidate status. Use time parameter as a string (day/month/year)
	void reportCandidate(int id, std::string job_types, long days, bool found_job,
		std::string date) const;

	//Reports candidate status. Use time parameter as a DateTime
	void reportCandidate(int id, std::string job_types, long days, bool found_job,
			const Poco::DateTime & date) const;

	//Reports job_opening status. Use time parameter as a string (day/month/year)
	void reportJobOpening(int sn, JobType job_type, long days, bool job_closed,
		std::string date) const;

	//Reports job_opening status. Use time parameter as a DateTime
	void reportJobOpening(int sn, JobType job_type, long days, bool job_closed,
			const Poco::DateTime & date) const;

	//Reports salary survey of a certain job_type. Use time parameter as a string (day/month/year)
	void reportSalarySurvey(JobType job_type, double average_salary,
			std::string sDate, std::string eDate) const;

	//Reports salary survey of a certain job_type. Use as a DateTime
	void reportSalarySurvey(JobType job_type, double average_salary,
			const Poco::DateTime & sDate, const Poco::DateTime& eDate) const;

	//Reports salary survey of a certain skill. Use time parameter as a string (day/month/year)
	void reportSalarySurvey(const SkillType* skill, double average_salary,
			std::string sDate, std::string eDate) const;

	//Reports salary survey of a certain skill. Use as a DateTime
	void reportSalarySurvey(const SkillType* skill, double average_salary,
			const Poco::DateTime & sDate, const Poco::DateTime& eDate) const;

	//Reports profit of HRC. Use time parameter as a string (day/month/year)
	void reportProfit(long profit, std::string sDate, std::string eDate) const;

	//Reports profit of a user. Use time parameter as a DateTime
	void reportProfit(long profit, const Poco::DateTime & sDate,
			const Poco::DateTime& eDate) const;


 private:
	//members
	std::string m_FirstId;
	std::string m_SecondId;
	bool m_Test;

	std::string toStr(const Poco::DateTime& date) const;
 
};



#endif
