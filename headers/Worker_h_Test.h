/** 
 * Generated CppUnit test driver template.
 * To build it, add the following line at the end of
 * your existing Makefile:
 *    include headers/Worker_h_Test.mk
 * Build the headers/Worker_h_Test target from the Make Target view
 */

#ifndef TEST_Worker_h_Test
#define TEST_Worker_h_Test

#ifdef ECUT_MAIN

#include "cppunit/extensions/HelperMacros.h"
#include "../headers/Worker.h"

class Worker_h_Test : public CPPUNIT_NS::TestFixture {
public:
	void setUp();
	void tearDown();
	void testWorker();
	void testcopy();
	void testgetID();
	void testgetSkills();
	void testgetDesiredJobTypes();
	void testgetExpectedSalary();
	void testgetOrigin();
	CPPUNIT_TEST_SUITE(Worker_h_Test);
	CPPUNIT_TEST(testWorker);
	CPPUNIT_TEST(testcopy);
	CPPUNIT_TEST(testgetID);
	CPPUNIT_TEST(testgetSkills);
	CPPUNIT_TEST(testgetDesiredJobTypes);
	CPPUNIT_TEST(testgetExpectedSalary);
	CPPUNIT_TEST(testgetOrigin);
	CPPUNIT_TEST_SUITE_END();
};

#endif /* ECUT_MAIN */

#endif /*WORKER_H_TEST*/
