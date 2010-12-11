// READFILE.h

#ifndef READFILE_H
#define READFILE_H

#include <string>
#include <vector>

#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"

#include "../include/HRC.h"

class ReadFile : public Poco::Util::IniFileConfiguration
{
public:
	Poco::DateTime *time;
	CAppLogger *logger;

	// Constructor that receive data stream as std::istream
	ReadFile(std::istream& istr);

	// Constructor that receive path as std::string
	ReadFile(const std::string& path);
	/////////////////////////////////////////////////////////////////////////

	// Destructor
	virtual ~ReadFile();

	void getConfig(Poco::DateTime *date, int *jobNum, int *workNum,int *seekerRep
			,int *companyRep,int *HrcStrag,int *logConP,int *logfileP);

	int getWorkers(std::vector<s_p_Worker> *workers);

	int getCompanies(std::vector<s_p_Company> *companies);

	int getJobs(std::vector<s_p_Job> *jobs);

	int getCommands(std::vector<Command> *commands);


	void setTime(Poco::DateTime *_time) {
		time=_time;
	}

	void setLogger(CAppLogger *_logger) {
		logger=_logger;
	}


};

#endif //

