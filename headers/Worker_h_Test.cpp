
#ifdef ECUT_MAIN
#include "../headers/Worker_h_Test.h"
#include <iterator>
#include <algorithm>
#include "Company.h"
#include "Poco/Random.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Worker_h_Test);


void Worker_h_Test::setUp()
{
}
void Worker_h_Test::tearDown()
{
}

void Worker_h_Test::testgetID() {
	Poco::Random rnd = Poco::Random(256);
	int ID = rnd.next();
	bool skills[6];
	bool desiredJobTypes[6];
	for (int i=0;i < 6; i++) {
		skills[i]= rnd.nextbool();
		desiredJobTypes[i]= rnd.nextbool();
	}
	int expectedSalary = rnd.next();
	Worker worker(ID,skills,desiredJobTypes,expectedSalary);
	CPPUNIT_ASSERT(worker.getID() == ID);
}

void Worker_h_Test::testgetSkills() {
	Poco::Random rnd = Poco::Random(256);
	int ID = rnd.next();
	bool skills[6];
	bool desiredJobTypes[6];
	for (int i=0;i < 6; i++) {
		skills[i]= rnd.nextbool();
		desiredJobTypes[i]= rnd.nextbool();
	}
	int expectedSalary = rnd.next();
	Worker worker(ID,skills,desiredJobTypes,expectedSalary);
	bool temp[6];
	worker.getSkills(temp);
	bool flag=true;
	for (int i=0;i < 6; i++) {
		if (temp[i] != skills[i])
			flag=false;
	}
	CPPUNIT_ASSERT(flag);
}

void Worker_h_Test::testgetDesiredJobTypes() {
	Poco::Random rnd = Poco::Random(256);
	int ID = rnd.next();
	bool skills[6];
	bool desiredJobTypes[6];
	for (int i=0;i < 6; i++) {
		skills[i]= rnd.nextbool();
		desiredJobTypes[i]= rnd.nextbool();
	}
	int expectedSalary = rnd.next();
	Worker worker(ID,skills,desiredJobTypes,expectedSalary);
	bool temp[6];
	worker.getDesiredJobTypes(temp);
	bool flag=true;
	for (int i=0;i < 6; i++) {
		if (temp[i] != desiredJobTypes[i])
			flag=false;
	}
	CPPUNIT_ASSERT(flag);
}
}

void Worker_h_Test::testgetExpectedSalary() {
	Poco::Random rnd = Poco::Random(256);
	int ID = rnd.next();
	bool skills[6];
	bool desiredJobTypes[6];
	for (int i=0;i < 6; i++) {
		skills[i]= rnd.nextbool();
		desiredJobTypes[i]= rnd.nextbool();
	}
	int expectedSalary = rnd.next();
	Worker worker(ID,skills,desiredJobTypes,expectedSalary);
	CPPUNIT_ASSERT(worker.getExpectedSalary() == expectedSalary);
}

void Worker_h_Test::testcopy() {
	Poco::Random rnd = Poco::Random(256);
	int ID = rnd.next();
	bool skills[6];
	bool desiredJobTypes[6];
	for (int i=0;i < 6; i++) {
		skills[i]= rnd.nextbool();
		desiredJobTypes[i]= rnd.nextbool();
	}
	int expectedSalary = rnd.next();
	Worker worker(ID,skills,desiredJobTypes,expectedSalary);
	Worker workerCopy=worker.copy();
	bool flag=true;
	if (workerCopy.getID != ID)  flag = flase;
	bool skillsCopy[6];
	workerCopy.getSkills(skillsCopy);
	bool desireCopy[6];
	workerCopy.getDesiredJobTypes(desireCopy);
	for (int i=0;i < 6; i++) {
		if ((skills[i] != skillsCopy[i]) || (desiredJobTypes[i] != desireCopy[i]))
			flag=false;
	}
	if (workerCopy.getExpectedSalary != expectedSalary)  flag = false;
	if (workerCopy.getOrigin != worker) flag=false;
	CPPUNIT_ASSERT(flag);
}

void Worker_h_Test::testgetOrigin() {
	Poco::Random rnd = Poco::Random(256);
	int ID = rnd.next();
	bool skills[6];
	bool desiredJobTypes[6];
	for (int i=0;i < 6; i++) {
		skills[i]= rnd.nextbool();
		desiredJobTypes[i]= rnd.nextbool();
	}
	int expectedSalary = rnd.next();
	Worker worker(ID,skills,desiredJobTypes,expectedSalary);
	CPPUNIT_ASSERT(worker.origin == null);
}

#endif /* ECUT_MAIN */

