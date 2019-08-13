#pragma once
#include <iostream>

namespace utilities
{
	class Test
	{
	public:
		Test() = default;
		virtual ~Test() = default;

	public:
		//Test.
		void test()
		{
			//Print info.
			const std::string testName = "[" + std::string(typeid(*this).name()) + "]";
			std::cout << "\n" << testName << " Starting Test.\n";

			//Run the actual test.
			onTest();

			//Print info
			std::cout << "\n" << testName << " Ending Test.\n" << std::endl;
			std::cout << "- - - - - - - - - -" << std::endl;
		}

	protected:
		/*
		 * Test this test.
		 */
		virtual void onTest() = 0;
	};
}
