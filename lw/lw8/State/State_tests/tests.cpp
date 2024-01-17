#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include "../State/GumBallMachineWithState.h"

class GumballMachineWithStateMock : public with_state::CGumballMachine
{
public:
	GumballMachineWithStateMock(unsigned numBalls)
		: with_state::CGumballMachine(numBalls)
	{}

	unsigned GetBallsCount() const override
	{
		return with_state::CGumballMachine::GetBallsCount();
	}
	with_state::CSoldOutState const& GetSoldOutState()
	{
		return with_state::CGumballMachine::GetSoldOutState();
	}
	with_state::CNoQuarterState const& GetNoQuarterState()
	{
		return with_state::CGumballMachine::GetNoQuarterState();
	}
	with_state::CSoldState const& GetSoldState()
	{
		return with_state::CGumballMachine::GetSoldState();
	}
	with_state::CHasQuarterState const& GetHasQuarterState()
	{
		return with_state::CGumballMachine::GetHasQuarterState();
	}
	const with_state::IState* GetState()
	{
		return with_state::CGumballMachine::GetState();
	}
};

SCENARIO("testing soldOut state")
{
	GumballMachineWithStateMock mockMachine(0);

	REQUIRE(mockMachine.GetBallsCount() == 0);
	REQUIRE(mockMachine.GetState() == &mockMachine.GetSoldOutState());

	WHEN("ejecting quarter")
	{
		mockMachine.EjectQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetSoldOutState());
	}

	WHEN("inserting quarter")
	{
		mockMachine.InsertQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetSoldOutState());
	}

	WHEN("turnCranck quarter")
	{
		mockMachine.TurnCrank();
		REQUIRE(mockMachine.GetBallsCount() == 0);
		REQUIRE(mockMachine.GetState() == &mockMachine.GetSoldOutState());
	}
}

SCENARIO("testing noQuarterState state")
{
	GumballMachineWithStateMock mockMachine(3);

	REQUIRE(mockMachine.GetBallsCount() == 3);
	REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());

	WHEN("ejecting quarter")
	{
		mockMachine.EjectQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
	}

	WHEN("inserting quarter")
	{
		mockMachine.InsertQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetHasQuarterState());
	}

	WHEN("turnCranck quarter")
	{
		mockMachine.TurnCrank();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
	}
}

SCENARIO("testing haveQuarterState state")
{
	GumballMachineWithStateMock mockMachine(3);
	
	mockMachine.InsertQuarter();

	WHEN("ejecting quarter")
	{
		mockMachine.EjectQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
	}

	WHEN("inserting quarter")
	{
		mockMachine.InsertQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetHasQuarterState());
	}

	WHEN("turnCranck quarter")
	{
		mockMachine.TurnCrank();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
	}
}

SCENARIO("testing soldState state")
{
	GIVEN("gumballMachine without gumballs in soldState")
	{
		GumballMachineWithStateMock mockMachine(1);

		mockMachine.InsertQuarter();
		mockMachine.TurnCrank();

		REQUIRE(mockMachine.GetState() == &mockMachine.GetSoldOutState());
		REQUIRE(mockMachine.GetBallsCount() == 0);
	}

	GIVEN("gumballMachine with gumballs in soldState")
	{
		GumballMachineWithStateMock mockMachine(2);

		mockMachine.InsertQuarter();
		mockMachine.TurnCrank();

		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
		REQUIRE(mockMachine.GetBallsCount() == 1);
	}
}