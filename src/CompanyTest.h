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
#include "../headers/Company.h"

class CompanyTest : public CPPUNIT_NS::TestFixture {
public:
	void setUp();
	void tearDown();
	CPPUNIT_TEST_SUITE(CompanyTest);
	CPPUNIT_TEST_SUITE_END();
	Company c;
};

#endif /* ECUT_MAIN */

#endif /*COMPANYTEST*/
