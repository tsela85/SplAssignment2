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

	// Constructor that receive data stream as std::istream
	ReadFile(std::istream& istr);

	// Constructor that receive path as std::string
	ReadFile(const std::string& path);
	/////////////////////////////////////////////////////////////////////////

	// Destructor
	virtual ~ReadFile();

	void getConfig(Poco::DateTime *date, int *jobNum, int *workNum,int *seekerRep
			,int *companyRep,int *HrcStrag,int *logConP,int *logfileP);

	void getWorkers(std::vector<s_p_Worker> *workers,Poco::DateTime *time,CAppLogger *logger);

	void getCompanies(std::vector<s_p_Company> *companies);

	void getJobs(std::vector<s_p_Job> *jobs);

	void getCommands(std::vector<Command> *commands);


};

#endif //

