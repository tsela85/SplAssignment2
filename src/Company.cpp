/*
 * Company.cpp
 *
 *  Created on: Dec 6, 2010
 *      Author: Tom and Aviad
 */

#include "../include/Company.h"

//class Company {
//private:
//	string name;
//	int type;
//	int SN;
//	vector<Job> jobOpenings;
//	int recruitingPolicy;
//	float QL_Min;




/**
 * ctor
 */
Company::Company(string _name, int _type, int _SN, int _recruitingPolicy,
		float _QL_Min) {
	name = _name;
	type = _type;
	SN = _SN;
	recruitingPolicy = _recruitingPolicy;
	QL_Min = _QL_Min;
	jobOpenings = vector<Job> ();
}

/**
 * destructor (??)
 *
Company::~Company() {
	// the vector is destroyed automagically.
}
*/
/**
 * copy ctor, create a copy of all of the fields

Company::Company(const Company& c) {
	name = c.getName();
	type = type;
	SN = SN;
	recruitingPolicy = recruitingPolicy;
	QL_Min = QL_Min;
	jobOpenings = vector<Job> ();

}*/
//};
