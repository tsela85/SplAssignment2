#ifndef JobType_H
#define JobType_H

//SPL 2011
//Assignment 2
//JobType.h
//Last change 26/11/2010


#define ASS2_LINUX

#include <string>

namespace ass2 {

class JobType {
public:

	enum EjobType {
		DATA_STORAGE, DIGITAL_MEDIA, E_COMMERCE, GAMING, RT, SECURITY
	};

	JobType() {
	}

	JobType(EjobType job_type) :
		m_jobType(job_type) {
	}

	JobType(std::string job_type) {
		if ("data_storage" == job_type)
			m_jobType = DATA_STORAGE;
		else if ("digital_media" == job_type)
			m_jobType = DIGITAL_MEDIA;
		else if ("e_commerce" == job_type)
			m_jobType = E_COMMERCE;
		else if ("gaming" == job_type)
			m_jobType = GAMING;
		else if ("rt" == job_type)
			m_jobType = RT;
		else if ("security" == job_type)
			m_jobType = SECURITY;
	}

	std::string PrettyPrint() const {
		switch (m_jobType) {
		case DATA_STORAGE:
			return "Data Storage";
		case DIGITAL_MEDIA:
			return "Digital Media Services";
		case E_COMMERCE:
			return "E-Commerce";
		case GAMING:
			return "Gaming";
		case RT:
			return "Real-Time Embedded Systems";
		case SECURITY:
			return "Security";
		default:
			return "No such job";
			//last line is just to make the compiler happy.
		}
	}

	int to_num() const {
		switch (m_jobType) {
		case DATA_STORAGE:
			return 0;
		case DIGITAL_MEDIA:
			return 1;
		case E_COMMERCE:
			return 2;
		case GAMING:
			return 3;
		case RT:
			return 4;
		case SECURITY:
			return 5;
		default:
			return 666;
			//last line is just to make the compiler happy.
		}
	}

private:
	EjobType m_jobType;
};

std::ostream& operator <<(std::ostream& os, JobType job_type);

}
;//namespace
#endif
