/*
 * SkillType.cpp
 *
 *  Created on: Nov 26, 2010
 */
#include "SkillType.h"

namespace ass2
{

	std::ostream& operator << (std::ostream& os, SkillType skill)
	{
		os << skill.PrettyPrint();
		return os;
	}
}
