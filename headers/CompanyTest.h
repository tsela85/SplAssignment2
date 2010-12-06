/** 
 * Generated CppUnit test driver template.
 * To build it, add the following line at the end of
 * your existing Makefile:
 *    include src/CompanyTest.mk
 * Build the src/CompanyTest target from the Make Target view
 */

#ifndef TEST_CompanyTest
#define TEST_CompanyTest

#ifdef ECUT_MAIN

#include "cppunit/extensions/HelperMacros.h"

class CompanyTest : public CPPUNIT_NS::TestFixture {
public:
	void setUp();
	void tearDown();
	void testCompany();
	void testDCompany();
	void testCompany_1();
	CPPUNIT_TEST_SUITE(CompanyTest);
	CPPUNIT_TEST(testCompany);
	CPPUNIT_TEST(testDCompany);
	CPPUNIT_TEST(testCompany_1);
	CPPUNIT_TEST_SUITE_END();
};

#endif /* ECUT_MAIN */

#endif /*COMPANYTEST*/
