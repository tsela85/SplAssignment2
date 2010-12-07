#ifdef ECUT_MAIN
#include "Company_h_Test.h"
#include <iterator>
#include <algorithm>
#include "Company.h"
#include "Poco/Random.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Company_h_Test);

/**
 * using Poco's (pseudo) Random generator for generating the parameters
 */
void Company_h_Test::setUp()
{
}
void Company_h_Test::tearDown()
{
}

void Company_h_Test::testgetName() {
	Poco::Random rnd = Poco::Random(256);
	int type = rnd.next(6);
	int SN = rnd.next();
	int recPol = rnd.next(6);
	float QL_Min = rnd.nextFloat();
	string rndstr0 = "";
	int iMax = rnd.next(20);
	for (int i = 0; i < iMax; ++i) {
		rndstr0 = rnd.nextChar() + rndstr0;
	}
	string rndstr = rndstr0;
	vector<Job> vec();
	c.type = type;
	c.SN = SN;
	c.recruitingPolicy = recPol;
	c.QL_Min = QL_Min;
	CPPUNIT_ASSERT(c.getName() == rndstr);
}

void Company_h_Test::testgetType() {
	Poco::Random rnd = Poco::Random(256);
	int type = rnd.next(6);
	int SN = rnd.next();
	int recPol = rnd.next(6);
	float QL_Min = rnd.nextFloat();
	string rndstr0 = "";
	int iMax = rnd.next(20);
	for (int i = 0; i < iMax; ++i) {
		rndstr0 = rnd.nextChar() + rndstr0;
	}
	string rndstr = rndstr0;
	vector<Job> vec();
	c.type = type;
	c.SN = SN;
	c.recruitingPolicy = recPol;
	c.QL_Min = QL_Min;
	CPPUNIT_ASSERT(type == c.getType());
}

void Company_h_Test::testgetSN() {
	Poco::Random rnd = Poco::Random(256);
	int type = rnd.next(6);
	int SN = rnd.next();
	int recPol = rnd.next(6);
	float QL_Min = rnd.nextFloat();
	string rndstr0 = "";
	int iMax = rnd.next(20);
	for (int i = 0; i < iMax; ++i) {
		rndstr0 = rnd.nextChar() + rndstr0;
	}
	string rndstr = rndstr0;
	vector<Job> vec();
	c.type = type;
	c.SN = SN;
	c.recruitingPolicy = recPol;
	c.QL_Min = QL_Min;
	CPPUNIT_ASSERT(SN == c.getSN());
}

void Company_h_Test::testgetJobOpenings() {
	Poco::Random rnd = Poco::Random(256);
	int type = rnd.next(6);
	int SN = rnd.next();
	int recPol = rnd.next(6);
	float QL_Min = rnd.nextFloat();
	string rndstr0 = "";
	int iMax = rnd.next(20);
	for (int i = 0; i < iMax; ++i) {
		rndstr0 = rnd.nextChar() + rndstr0;
	}
	string rndstr = rndstr0;
	vector<Job> vec();
	c.type = type;
	c.SN = SN;
	c.recruitingPolicy = recPol;
	c.QL_Min = QL_Min;
	bool result = std::equal( vec.begin(), vec.end(), c.getJobOpenings().begin() );
	CPPUNIT_ASSERT(result);
}

void Company_h_Test::testgetRecruitingPolicy() {
	Poco::Random rnd = Poco::Random(256);
	int type = rnd.next(6);
	int SN = rnd.next();
	int recPol = rnd.next(6);
	float QL_Min = rnd.nextFloat();
	string rndstr0 = "";
	int iMax = rnd.next(20);
	for (int i = 0; i < iMax; ++i) {
		rndstr0 = rnd.nextChar() + rndstr0;
	}
	string rndstr = rndstr0;
	vector<Job> vec();
	c.type = type;
	c.SN = SN;
	c.recruitingPolicy = recPol;
	c.QL_Min = QL_Min;
	CPPUNIT_ASSERT(recPol == c.getRecruitingPolicy());
}

void Company_h_Test::testgetQL_Min() {
	Poco::Random rnd = Poco::Random(256);
	int type = rnd.next(6);
	int SN = rnd.next();
	int recPol = rnd.next(6);
	float QL_Min = rnd.nextFloat();
	string rndstr0 = "";
	int iMax = rnd.next(20);
	for (int i = 0; i < iMax; ++i) {
		rndstr0 = rnd.nextChar() + rndstr0;
	}
	string rndstr = rndstr0;
	vector<Job> vec();
	c.type = type;
	c.SN = SN;
	c.recruitingPolicy = recPol;
	c.QL_Min = QL_Min;
	CPPUNIT_ASSERT(QL_Min == c.getQL_Min());
}

#endif /* ECUT_MAIN */

