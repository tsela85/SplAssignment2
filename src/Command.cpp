/*
 * Command.cpp
 *
 *  Created on: Dec 11, 2010
 *      Author: tom
 */
#include "../include/Command.h"

CommandType convertCommand(string command) {
	CommandType temp=ERROR;
	if (command == "candidateReport") {
		temp = CANDIDATEREPORT;
	} else
	if (command == "jobOpeningReport") {
		temp=JOBOPENINGREPORT;
	} else
	if (command == "salarySurveyReportByJob") {
		temp=SALARYSURVEYREPORTBYJOB;
	} else
	if (command == "salarySurveyReportBySkill") {
		temp=SALARYSURVEYREPORTBYSKILL;
	} else
	if (command == "profitReport") {
		temp=PROFITREPORT;
	} else
	if (command == "terminate") {
		temp=TERMINATE;
	}
	return temp;
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
		case SALARYSURVEYREPORTBYJOB: hrc->reportSalarySurvey(JobType(kind),date, endDate); break;
		case SALARYSURVEYREPORTBYSKILL:hrc->reportSalarySurvey(SkillType(kind), date,endDate); break;
		case PROFITREPORT: hrc->reportProfit(date,endDate); break;
		case TERMINATE: hrc->terminateProgram(); break;
		case ERROR: break;
		default: break;
	}
}

Poco::DateTime Command::getDate() {
	switch (type) {
		case CANDIDATEREPORT: return date;
		case JOBOPENINGREPORT:return date;
		case SALARYSURVEYREPORTBYJOB: return endDate;
		case SALARYSURVEYREPORTBYSKILL: return endDate;
		case PROFITREPORT: return endDate;
		case TERMINATE: return date;
		case ERROR: break;
		default: break;
	}
	return date;
}


