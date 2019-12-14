#pragma once
#include "../Test.h"
#include "../../state/FSM.h"

namespace utilities
{
	enum class StateType
	{
		IDLE_STATE,
		BUSY_STATE
	};


	//Forward declare some stuff
	class StateTest;

	/*
	 * Idle state for testing
	 */
	class IdleState : public BaseState<StateType, StateTest>
	{
	public:
		void onEnter(StateTest& object) override
		{
			std::cout << "Now entering idle state!" << std::endl;
		}

		StateType onUpdate(unsigned tick, unsigned ticksPassed, StateTest& object) override
		{
			//Always stay idle.
			return StateType::IDLE_STATE;
		}

		void onLeave(StateTest& object) override
		{
			//Print something about leaving
			std::cout << "Now leaving idle state!" << std::endl;
		}

		bool onRequestStateChange(StateType state) override
		{
			//Allow state to change always, no  special conditions.
			return true;
		}

		BaseState* clone() override
		{
			return new IdleState(*this);
		}

	};


	/*
	 * Busy state
	 */
	class BusyState : public BaseState<StateType, StateTest>
	{
	public:
		void onEnter(StateTest& object) override
		{
			std::cout << "Now entering busy state!" << std::endl;
		}

		StateType onUpdate(unsigned tick, unsigned ticksPassed, StateTest& object) override
		{
			i += ticksPassed;

			//After 30 ticks go back to idling.
			if (i > 30)
			{
				return StateType::IDLE_STATE;
			}

			std::cout << "Still busy for " << (30 - i) << " ticks." << std::endl;

			//Keep being busy.
			return StateType::BUSY_STATE;
		}

		void onLeave(StateTest& object) override
		{
			//Print something about leaving
			std::cout << "Now leaving busy state!" << std::endl;
		}

		bool onRequestStateChange(StateType state) override
		{
			//Allow state to change always, no  special conditions.
			return true;
		}

		BaseState* clone() override
		{
			return new BusyState(*this);
		}

	private:
		int i = 0;
	};

	class StateTest : public Test
	{
	public:
		void onTest() override
		{
			//Perform the state test

			//Tick counter.
			std::uint16_t tick = 0;

			/*
			 * Create a FSM that is owned by this class (StateTest).
			 * It uses the enum StateType to indicate its states.
			 * It starts at tick 0.
			 */
			FSM<StateType, StateTest> fsm(StateType::IDLE_STATE, tick);

			//Register some states with the FSM.
			fsm.registerState(StateType::IDLE_STATE, new IdleState());
			fsm.registerState(StateType::BUSY_STATE, new BusyState());

			//Just be idle for one tick.
			fsm.update(++tick, *this);

			//Set to busy.
			fsm.requestState(StateType::BUSY_STATE, *this);

			//Simulate game ticks.
			for(int i = 0; i < 40; ++i)
			{
				fsm.update(++tick, *this);
			}
		}
	};


}
