/*
 * Company.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */
#include <string>
#include <vector>
#include "../headers/defs.h"

#ifndef COMPANY_H_
#define COMPANY_H_

using namespace std;
// for company types:
#define DATA_STORAGE 0;
#define DIGITAL_MEDIA 1;
#define E_COMMERCE 2;
#define GAMING 3;
#define RT 4;
#define SECURITY 5;


class Company {
	string name;
	int type;
	int SN;
	vector<job> jobOpenings;
	int recruitingPolicy;
	float QL_Min;
};

#endif /* COMPANY_H_ */
