#pragma once
#include "../Test.h"
#include "../memory/MemoryPool.h"

namespace utilities
{
	class MPTest : public Test
	{
	public:
		/*
		 * Test memory pools.
		 */
		void onTest() override
		{
			const int size = 50;

			//Make a memory pool.
			MemoryPool<double> mp(size);

			std::vector<MP_Ptr<double>> allocated;

			//Allocate and deallocate stuff.
			for(int i = 0; i < size * 10; ++i)
			{
				std::cout << "Pool size: " << size << " Free: " << mp.getFreeSlots() << " Taken: " << mp.getObjectCount() << std::endl;

				allocated.push_back(mp.allocate());

				if(allocated.size() > size - 2)
				{
					allocated.clear();
				}
			}
		}
	};
}
