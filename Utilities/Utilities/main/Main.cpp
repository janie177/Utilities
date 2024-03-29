/*
 * Utilities is a library which contains useful classes.
 * They can be copy-pasted to other projects as needed.
 *
 * This project can be executed from the console in order to test the various classes it provides.
 */

#include <cstdio>
#include "../test/Test.h"
#include <vector>
#include "../test/impl/FileTest.h"
#include "../test/impl/MPTest.h"
#include "../test/impl/GameLoopTest.h"
#include "../test/impl/StateTest.h"

int main()
{
	using namespace utilities;

	/*
	 * Create a container for all the tests.
	 */
	std::vector<Test*> tests;

	/*
	 * Add all tests to be executed.
	 */
	tests.emplace_back(new FileTest());
	tests.emplace_back(new MPTest());
	tests.emplace_back(new GameLoopTest());
	tests.emplace_back(new StateTest());




	/*
	 * Execute all the tests.
	 */
	for(auto& test : tests)
	{
		test->test();
	}



	/*
	 * Free memory.
	 */
	for(auto& test : tests)
	{
		delete test;
	}

	//Shutdown
	getchar();
	return 0;
}
