/*
 * Company.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */

#ifndef COMPANY_H_
#define COMPANY_H_

#include <string>
#include <vector>
//#include "../include/defs.h"
#include "../include/Job.h"

using namespace std;

class Company {
public:
	Company();

	Company(string name, int type, int SN, int recruitingPolicy, float QL_Min);
//	~Company();
	//	Company(const Company& c); shallow copy - no need for a ctor.
	string getName() {
		return name;
	}
	int getType() {
		return type;
	}
	int getSN() {
		return SN;
	}
	vector<Job> getJobOpenings(){
		return jobOpenings;
	}
	int getRecruitingPolicy(){
		return recruitingPolicy;
	}
	float getQL_Min() {
		return QL_Min;
	}
//private:
	string name;
	int type;
	int SN;
	vector<Job> jobOpenings;
	int recruitingPolicy;
	float QL_Min;
};


#endif /* COMPANY_H_ */
