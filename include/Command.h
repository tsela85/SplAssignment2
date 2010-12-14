/*
 * Command.h
 *
 *  Created on: Dec 11, 2010
 *      Author: tom
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>

#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"
#include "../include/HRC.h"

using namespace std;

enum CommandType
{
	CANDIDATEREPORT,
	JOBOPENINGREPORT,
	SALARYSURVEYREPORTBYJOB,
	SALARYSURVEYREPORTBYSKILL,
	PROFITREPORT,
	TERMINATE,
	ERROR
};
CommandType convertCommand(string command);

class HRC;

class Command {

public:


	CommandType type;
	Poco::DateTime date;
	Poco::DateTime endDate;
	int ID;
	string kind;

	Command(CommandType type,Poco::DateTime date,int ID);

	Command(CommandType type,string kind,Poco::DateTime date,Poco::DateTime endDate);

	Command(CommandType type,Poco::DateTime date,Poco::DateTime endDate);

	Command(CommandType type,Poco::DateTime date);

	void executeCommand(HRC *hrc);

	Poco::DateTime getDate();
};




#endif /* COMMAND_H_ */
