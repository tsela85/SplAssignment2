/*
 * Command.cpp
 *
 *  Created on: Dec 11, 2010
 *      Author: tom
 */
#include "../include/Command.h"

CommandType convertCommand(string command) {
	CommandType temp;
	if (command == "candidateReport") {
		temp = CANDIDATEREPORT;
		return temp;
	}
	if (command == "jobOpeningReport") {
		temp=JOBOPENINGREPORT;
		return temp;
	}
	if (command == "salarySurveyReportByJob") {
		temp=SALARYSURVEYREPORTBYJOB;
		return temp;
	}
	if (command == "salarySurveyReportBySkill") {
		temp=SALARYSURVEYREPORTBYSKILL;
		return temp;
	}
	if (command == "profitReport") {
		temp=PROFITREPORT;
		return temp;
	}
	if (command == "terminate") {
		temp=TERMINATE;
		return temp;
	}
}

Command::Command(CommandType _type,Poco::DateTime _date,int _ID) {
	type=_type;
	date=_date;
	ID=_ID;
}
Command::Command(CommandType _type,int _kind,Poco::DateTime _date,Poco::DateTime _endDate) {
	type=_type;
	date=_date;
	kind=_kind;
	endDate=_endDate;
}
Command::Command(CommandType _type,Poco::DateTime _date,Poco::DateTime _endDate) {
	type=_type;
	date=_date;
	endDate=_endDate;
}
Command::Command(CommandType _type,Poco::DateTime _date) {
	type=_type;
	date=_date;
}


