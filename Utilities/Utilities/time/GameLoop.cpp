#include "GameLoop.h"
#include <thread>
#include <algorithm>

namespace utilities
{
	GameLoop::GameLoop(std::uint32_t fps, std::uint32_t tps) :
		fps(fps), tps(tps), currentTick(0), fpsSamples{0.f, 0.f, 1.f}, tpsSamples{0.f, 0.f, 1.f}, sampleInterval(1.f) 
	{
		frameDelay = 1000000.f / static_cast<std::float_t>(fps);
		tickDelay = 1000000.f / static_cast<std::float_t>(tps);
		currentTime = std::chrono::high_resolution_clock::now();
		lastFrame = std::chrono::high_resolution_clock::now();
		lastTick = std::chrono::high_resolution_clock::now();
	}
	GameLoopData GameLoop::update()
	{
		currentTime = std::chrono::high_resolution_clock::now();
		const auto tickTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTick).count();
		const auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastFrame).count();

		const auto timeTillFrame = frameDelay - frameTime;
		const auto timeTillTick = tickDelay - tickTime;

		//Should a tick or frame happen? This is equal to 0 when it should.
		const auto minTime = std::max<long long>(0.f, std::min<long long>(timeTillFrame, timeTillTick));

		//Frame or tick should happen.
		if(minTime <= 0.f)
		{
			const bool frame = timeTillFrame <= 0.f;
			const bool tick = timeTillTick <= 0.f;

			//Samples for FPS and TPS. Also resetting counter.
			if(frame)
			{
				//Reset counter
				lastFrame = currentTime;

				//Increment time and count.
				fpsSamples[0] += (frameTime / 1000000.0f);
				++(fpsSamples[1]);

				//If a second has passed, 
				if (fpsSamples[0] > sampleInterval)
				{
					//Calculate frames per second.
					fpsSamples[2] = fpsSamples[1] / fpsSamples[0];
					fpsSamples[0] = 0.f;
					fpsSamples[1] = 0.f;
				}
			}
			if(tick)
			{
				//Reset counter.
				lastTick = currentTime;

				//Increment tick count.
				++currentTick;

				//Increment time and count.
				tpsSamples[0] += (tickTime / 1000000.0f);
				++(tpsSamples[1]);

				//If a second has passed, 
				if (tpsSamples[0] > sampleInterval)
				{
					//Calculate frames per second.
					tpsSamples[2] = tpsSamples[1] / tpsSamples[0];
					tpsSamples[0] = 0.f;
					tpsSamples[1] = 0.f;
				}
			}

			return GameLoopData
			{
				fpsSamples[2],
				tpsSamples[2],
				static_cast<std::float_t>(frameTime / 1000000.0f),
				static_cast<std::float_t>(tickTime / 1000000.0f),
				tick,
				frame,
				currentTick
			};
		}

		//Sleep till something does need to happen.
		std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(minTime)));

		//Recursively call to return data since enough time has passed.
		return update();
	}

	std::uint32_t GameLoop::getFpsTarget() const
	{
		return fps;
	}

	std::uint32_t GameLoop::getTpsTarget() const
	{
		return tps;
	}

	void GameLoop::setSampleInterval(std::float_t sampleInterval)
	{
		this->sampleInterval = sampleInterval;
	}
}


