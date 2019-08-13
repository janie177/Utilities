#pragma once
#include <chrono>
#include <glm/glm.hpp>

namespace utilities
{
	/*
	 * GameTimer is a class that can keep track of the main game loop.
	 * It has settings to control FPS and TPS.
	 */
	class GameTimer {
	private:
		bool do_frame;
		bool do_tick;

		std::int32_t fps;
		std::int32_t tps;
		std::float_t tickDelay;
		std::float_t microsBetweenFrames;
		std::float_t microsBetweenTicks;
		std::float_t frameDelay;
		std::uint64_t tick;

		std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame;
		std::chrono::time_point<std::chrono::high_resolution_clock> lastTick;
		std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;


		/*
		 * Samples to measure the TPS and FPS.
		 * The first value is the current time.
		 * The second value is the total amount of frames/ticks in that time.
		 * The third value is used to store the last sample.
		 *
		 * Every time a certain time has passed, the sample is updated by dividing total amount of frames/ticks through the time that has passed.
		 * The result is stored as the third value.
		 */
		glm::vec3 fpsSamples;
		glm::vec3 tpsSamples;

		//Interval to take samples at. Defaults to 1 second.
		std::float_t sampleInterval;

	public:
		GameTimer(std::int32_t fps, std::int32_t tps);
		void update();
		bool nextTick() const;
		bool nextFrame() const;

		//Get how far from the next tick we are
		std::float_t nextTickPct() const;

		/*
		 * The amount of seconds that have passed since a frame has happened.
		 * This is measured in real time, and is NOT equal to the difference between frames or ticks.
		 */
		std::float_t secondsSinceFrame() const;

		/*
		 * The amount of seconds that have passed since a tick has happened.
		 * This is measured in real time, and is NOT equal to the difference between frames or ticks.
		 */
		std::float_t secondsSinceTick() const;

		/*
		 * The amount of seconds between the current and last frame.
		 */
		std::float_t getDeltaTimeFrame() const;

		/*
		 * The amount of seconds between the current and last tick.
		 */
		std::float_t getDeltaTimeTick() const;

		/*
		 * See how many seconds are between FPS and TPS samples.
		 * FPS and TPS are averaged once this many samples.
		 */
		std::float_t sampleIntervalSeconds() const;

		/*
		 * Set the interval in seconds to measure FPS and TPS over.
		 * A short interval shows more recent values, but has more jitter.
		 * A longer period shows a smoother average.
		 */
		void setSampleIntervalSeconds(std::float_t interval);

		std::uint64_t getTick() const;
		std::float_t getActualFPS() const;
		std::float_t getActualTPS() const;
	};
}
