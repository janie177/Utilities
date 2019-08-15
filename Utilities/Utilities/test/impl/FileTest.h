#pragma once
#include "../Test.h"
#include "../../logging/Logger.h"
#include "../../file/FileReader.h"

namespace utilities
{
	class FileTest : public Test
	{
	public:
		//Test file related functionality.
		void onTest() override
		{
			Logger logger("test.txt");
			FileReader reader("test.txt");

			logger.log(Severity::INFO, "Testy mctestface");
			logger.saveToFile();

			reader.open();
			std::cout << "Contents of file:\n";
			while(reader.nextLine())
			{
				std::cout << reader.getCurrentLine() << "\n";
			}
			reader.close();

			logger.log(Severity::WARNING, "New log entry");
			logger.log(Severity::FATAL, "Another new log entry.");
			logger.saveToFile();


			reader.open();
			std::cout << "\nContents of file part 2:\n";
			while (reader.nextLine())
			{
				std::cout << reader.getCurrentLine() << "\n";
			}
			reader.close();			
		}
	};
}
