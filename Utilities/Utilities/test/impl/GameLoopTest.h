#pragma once
#include "../Test.h"
#include "../../time/GameLoop.h"

namespace utilities
{
	class GameLoopTest : public Test
	{
	public:
		void onTest() override
		{
			//Start a simple game loop with 10 and 3 fps respectively.
			GameLoop loop(1, 1);
			loop.setSampleInterval(3.f);

			for (int i = 0; i < 10000; ++i)
			{
				const auto result = loop.update();

				if(result.tick)
				{
					std::cout << "Tick!\n";
				}
				if(result.frame)
				{
					std::cout << "Frame!\n";
				}
				std::cout << "TPS: " << result.tps << "\n";
				std::cout << "FPS: " << result.fps << "\n";
				std::cout << std::flush;
			}
		}
	};
}
