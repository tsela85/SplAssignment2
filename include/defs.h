/*
 * defs.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Tom and Aviad
 */

#ifndef DEFS_H_
#define DEFS_H_

#include "boost/shared_ptr.hpp"
#include "../include/Worker.h"
//#include "../include/Company.h"
#include "../include/Job.h"

//typedef std::auto_ptr<Worker> a_p_Worker;
typedef boost::shared_ptr<Worker> s_p_Worker;
//typedef std::auto_ptr<Company> a_p_Company;
//typedef boost::shared_ptr<Company> s_p_Company;
//typedef std::auto_ptr<Job> a_p_Job;
typedef boost::shared_ptr<Job> s_p_Job;

// for skills:
#define _CPP 0
#define _JAVA 1
#define _SCRIPT 2
#define _WEB 3
#define _SYSTEM 4
#define _QA 5

// for desired job types:
#define _DATA_STORAGE 0
#define _DIGITAL_MEDIA 1
#define _E_COMMERCE 2
#define _GAMING 3
#define _RT 4
#define _SECURITY 5

//rec strategies
#define CHEAP 0
#define LAVISH 1
#define COST_EFFECTIVE 2

// HRC strategies
#define FAIR 0
#define EAGER 1




#endif /* DEFS_H_ */
