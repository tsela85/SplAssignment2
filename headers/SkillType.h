#ifndef SkillType_H
#define SkillType_H

//SPL 2011
//Assignment 2
//SkillType.h
//Last change 26/11/2010


#define ASS2_LINUX

#include <string>


namespace ass2{


	class SkillType
	{
	public:

		enum ESkillType
		{
			CPP,
			JAVA,
			SCRIPT,
			WEB,
			SYSTEM,
			QA
		};

		SkillType(ESkillType skill_type) : m_skillType(skill_type) {}

		SkillType(std::string skill)
		{
			if ("cpp" == skill)
				m_skillType =  CPP;
			else if ("java" == skill)
				m_skillType =  JAVA;
			else if ("script" == skill)
				m_skillType =  SCRIPT;
			else if ("web" == skill)
				m_skillType =  WEB;
			else if ("system" == skill)
				m_skillType =  SYSTEM;
			 else if ("qa" == skill)
				m_skillType =  QA;
		}


		std::string PrettyPrint() const
		{
			switch (m_skillType){
				case CPP :				return "C++ Developer";
				case JAVA :				return "Java Developer";
				case SCRIPT :	    	return "Script Languages";
				case WEB :			    return "Web Developer";
				case SYSTEM :		    return "System Administrator";
				case QA :			    return "Quality Assurance";
				default:				return "No such job";
				//last line is just to make the compiler happy.
			}
		}

	private:
		ESkillType m_skillType;
	};


	std::ostream& operator << (std::ostream& os, SkillType skill);

};//namespace
#endif
