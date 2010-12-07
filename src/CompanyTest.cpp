#ifdef ECUT_MAIN
#include "CompanyTest.h"
#include "Poco/Random.h"
#include "Company.cpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CompanyTest);

void CompanyTest::setUp()
{
	Poco::Random rnd = Poco::Random(255);
	int type = rnd.next(6);
	int SN = rnd.next();
	int recPol = rnd.next(6);
	float QL_Min = rnd.nextFloat();
	string rndstr = "";
	int iMax = rnd.next(20);
	for (int i = 0; i < iMax; ++i) {
		rndstr = rnd.nextChar() + rndstr;
	}
	Company c = Company(rndstr, type, SN, recPol, QL_Min);
}
void CompanyTest::tearDown()
{
}

#endif /* ECUT_MAIN */

