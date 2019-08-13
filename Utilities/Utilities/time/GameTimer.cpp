#include "GameTimer.h"

namespace utilities
{

	//Constructor which automatically calculates how long to wait between ticks and frames.
	//Use microseconds for good accuracy.
	GameTimer::GameTimer(std::int32_t fps, std::int32_t tps) : do_frame(false), do_tick(false), tick(0), fpsSamples(0.f, 0.f, 1.f), tpsSamples(0.f, 0.f, 1.f), sampleInterval(1.f)
	{
		this->fps = fps;
		this->tps = tps;
		frameDelay = 1000000.f / static_cast<std::float_t>(fps);
		tickDelay = 1000000.f / static_cast<std::float_t>(tps);
		microsBetweenFrames = 1000000.f;
		microsBetweenTicks = 1000000.f;
		currentTime = std::chrono::high_resolution_clock::now();
		lastFrame = std::chrono::high_resolution_clock::now();
		lastTick = std::chrono::high_resolution_clock::now();
	}

	//Method which updates the current time inside the class.
	void GameTimer::update()
	{
		do_frame = false;
		do_tick = false;
		currentTime = std::chrono::high_resolution_clock::now();

		const std::float_t microsFrame = static_cast<std::float_t>(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastFrame).count());
		if (microsFrame >= frameDelay)
		{
			microsBetweenFrames = microsFrame;
			lastFrame = currentTime;
			do_frame = true;

			//Increment time and count.
			fpsSamples.x += (microsBetweenFrames / 1000000.0f);
			++(fpsSamples.y);

			//If a second has passed, 
			if (fpsSamples.x > sampleInterval)
			{
				//Calculate frames per second.
				fpsSamples.z = fpsSamples.y / fpsSamples.x;
				fpsSamples.x = 0.f;
				fpsSamples.y = 0.f;
			}
		}

		const std::float_t microsTick = static_cast<std::float_t>(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTick).count());
		if (microsTick >= tickDelay)
		{
			microsBetweenTicks = microsTick;
			lastTick = currentTime;
			++tick;
			do_tick = true;

			//Increment time and count.
			tpsSamples.x += (microsBetweenTicks / 1000000.0f);
			++(tpsSamples.y);

			//If a second has passed, 
			if (tpsSamples.x > sampleInterval)
			{
				//Calculate frames per second.
				tpsSamples.z = tpsSamples.y / tpsSamples.x;
				tpsSamples.x = 0.f;
				tpsSamples.y = 0.f;
			}
		}
	}

	bool GameTimer::nextFrame() const
	{
		return do_frame;
	}

	//See how far we are from the next tick. 1.0 is there, 0.0 is not there at all.
	std::float_t GameTimer::nextTickPct() const
	{
		const auto now = std::chrono::high_resolution_clock::now();
		const std::float_t microsSinceTick = static_cast<std::float_t>(std::chrono::duration_cast<std::chrono::microseconds>(now - lastTick).count());
		return microsSinceTick / microsBetweenTicks;
	}

	std::float_t GameTimer::secondsSinceFrame() const
	{
		const auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrame).count() / 1000000.0f;
	}

	std::float_t GameTimer::secondsSinceTick() const
	{
		const auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(now - lastTick).count() / 1000000.0f;
	}

	std::float_t GameTimer::getDeltaTimeFrame() const
	{
		return microsBetweenFrames / 1000000.0f;
	}

	std::float_t GameTimer::getDeltaTimeTick() const
	{
		return microsBetweenTicks / 1000000.0f;
	}

	std::float_t GameTimer::sampleIntervalSeconds() const
	{
		return sampleInterval;
	}

	void GameTimer::setSampleIntervalSeconds(std::float_t interval)
	{
		this->sampleInterval = interval;
	}

	std::uint64_t GameTimer::getTick() const
	{
		return tick;
	}

	std::float_t GameTimer::getActualFPS() const
	{
		return fpsSamples.z;
	}

	std::float_t GameTimer::getActualTPS() const
	{
		return tpsSamples.z;
	}

	bool GameTimer::nextTick() const
	{
		return do_tick;
	}
}