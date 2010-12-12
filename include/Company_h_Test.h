/** 
 * Generated CppUnit test driver template.
 * To build it, add the following line at the end of
 * your existing Makefile:
 *    include include/Company_h_Test.mk
 * Build the include/Company_h_Test target from the Make Target view
 */

#ifndef TEST_Company_h_Test
#define TEST_Company_h_Test

#ifdef ECUT_MAIN

#include "cppunit/extensions/HelperMacros.h"
#include "../include/Company.h"

class Company_h_Test : public CPPUNIT_NS::TestFixture {
public:
	void setUp();
	void tearDown();
	void testgetName();
	void testgetType();
	void testgetSN();
	void testgetJobOpenings();
	void testgetRecruitingPolicy();
	void testgetQL_Min();
	CPPUNIT_TEST_SUITE(Company_h_Test);
	CPPUNIT_TEST(testgetName);
	CPPUNIT_TEST(testgetType);
	CPPUNIT_TEST(testgetSN);
	CPPUNIT_TEST(testgetJobOpenings);
	CPPUNIT_TEST(testgetRecruitingPolicy);
	CPPUNIT_TEST(testgetQL_Min);
	CPPUNIT_TEST_SUITE_END();
	Company c;
};

#endif /* ECUT_MAIN */

#endif /*COMPANY_H_TEST*/
