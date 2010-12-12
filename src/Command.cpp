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
	} else
	if (command == "jobOpeningReport") {
		temp=JOBOPENINGREPORT;
		return temp;
	} else
	if (command == "salarySurveyReportByJob") {
		temp=SALARYSURVEYREPORTBYJOB;
		return temp;
	} else
	if (command == "salarySurveyReportBySkill") {
		temp=SALARYSURVEYREPORTBYSKILL;
		return temp;
	} else
	if (command == "profitReport") {
		temp=PROFITREPORT;
		return temp;
	} else
	if (command == "terminate") {
		temp=TERMINATE;
		return temp;
	}
	// TODO:	throw exeception ("somthing bad")
}

Command::Command(CommandType _type,Poco::DateTime _date,int _ID) {
	type=_type;
	date=_date;
	ID=_ID;
}
Command::Command(CommandType _type,string _kind,Poco::DateTime _date,Poco::DateTime _endDate) {
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

void Command::executeCommand(HRC *hrc) {
	switch (type) {
		case CANDIDATEREPORT: hrc->reportCandidate(ID,date); break;
		case JOBOPENINGREPORT: hrc->reportJobOpening(ID,date); break;
		case SALARYSURVEYREPORTBYJOB: hrc->reportSalarySurvey(kind,date, endDate); break;
		case SALARYSURVEYREPORTBYSKILL:hrc->reportSalarySurvey(kind, date,endDate); break;
		case PROFITREPORT: hrc->reportProfit(date,endDate); break;
		case TERMINATE: break;
		default: break;
	}
}


