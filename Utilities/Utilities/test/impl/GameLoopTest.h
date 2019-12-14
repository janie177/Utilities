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
			//Start a simple game loop.
			GameLoop loop(145, 61, true);
			loop.setSampleInterval(3.f);

			for (int i = 0; i < 500; ++i)
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
