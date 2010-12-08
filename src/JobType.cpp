/*
 * JobType.cpp
 *
 *  Created on: Nov 26, 2010
 */
#include "../include/JobType.h"

namespace ass2
{

	std::ostream& operator << (std::ostream& os, JobType job_type)
	{
		os << job_type.PrettyPrint();
		return os;
	}

}
