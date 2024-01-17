#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include "../StateWithFifthCoins/GumBallMachineWithState.h"
#include "../StateWithFifthCoins/NaiveGumBallMachine.h"

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
	unsigned GetCoinsCount() const override
	{
		return with_state::CGumballMachine::GetCoinsCount();
	}
	void IncreaseCoinsCount() override
	{
		with_state::CGumballMachine::IncreaseCoinsCount();
	}
};

SCENARIO("testing CGumballMachine with state soldOut state")
{
	GumballMachineWithStateMock mockMachine(0);

	REQUIRE(mockMachine.GetBallsCount() == 0);
	REQUIRE(mockMachine.GetState() == &mockMachine.GetSoldOutState());

	GIVEN("a machine with 0 coins")
	{
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

	GIVEN("a machine with 3 coins")
	{
		mockMachine.IncreaseCoinsCount();
		mockMachine.IncreaseCoinsCount();
		mockMachine.IncreaseCoinsCount();

		WHEN("ejecting quarter")
		{
			mockMachine.EjectQuarter();
			REQUIRE(mockMachine.GetState() == &mockMachine.GetSoldOutState());
			REQUIRE(mockMachine.GetCoinsCount() == 0);
		}
	}
}

SCENARIO("testing CGumballMachine with state noQuarterState state")
{
	GumballMachineWithStateMock mockMachine(3);

	REQUIRE(mockMachine.GetBallsCount() == 3);
	REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());

	WHEN("ejecting quarter")
	{
		mockMachine.EjectQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
		REQUIRE(mockMachine.GetCoinsCount() == 0);
	}

	WHEN("inserting quarter")
	{
		mockMachine.InsertQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetHasQuarterState());
		REQUIRE(mockMachine.GetCoinsCount() == 1);
	}

	WHEN("turnCranck quarter")
	{
		mockMachine.TurnCrank();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
		REQUIRE(mockMachine.GetCoinsCount() == 0);
	}
}

SCENARIO("testing CGumballMachine with state haveQuarterState state")
{
	GumballMachineWithStateMock mockMachine(3);

	mockMachine.InsertQuarter();
	REQUIRE(mockMachine.GetCoinsCount() == 1);

	WHEN("ejecting quarter")
	{
		mockMachine.EjectQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
		REQUIRE(mockMachine.GetCoinsCount() == 0);
	}

	WHEN("inserting quarter")
	{
		mockMachine.InsertQuarter();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetHasQuarterState());
		REQUIRE(mockMachine.GetCoinsCount() == 2);
	}

	WHEN("turnCranck quarter")
	{
		mockMachine.TurnCrank();
		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
		REQUIRE(mockMachine.GetCoinsCount() == 0);
	}

	WHEN("inserting quarter 5 times")
	{
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();

		REQUIRE(mockMachine.GetCoinsCount() == 5);
		REQUIRE(mockMachine.GetState() == &mockMachine.GetHasQuarterState());
	}

	WHEN("inserting quarter 6 times")
	{
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();

		REQUIRE(mockMachine.GetCoinsCount() == 5);
		REQUIRE(mockMachine.GetState() == &mockMachine.GetHasQuarterState());
	}
}

SCENARIO("dispense gumball CGumballMachine with state")
{
	GIVEN("gumballMachine without gumballs in soldState")
	{
		GumballMachineWithStateMock mockMachine(1);

		mockMachine.InsertQuarter();
		mockMachine.TurnCrank();

		REQUIRE(mockMachine.GetState() == &mockMachine.GetSoldOutState());
		REQUIRE(mockMachine.GetBallsCount() == 0);
	}

	GIVEN("gumballMachine with gumballs in soldState with one coin")
	{
		GumballMachineWithStateMock mockMachine(2);

		mockMachine.InsertQuarter();
		mockMachine.TurnCrank();

		REQUIRE(mockMachine.GetState() == &mockMachine.GetNoQuarterState());
		REQUIRE(mockMachine.GetBallsCount() == 1);
	}

	GIVEN("gumballMachine with gumballs in soldState with two coins")
	{
		GumballMachineWithStateMock mockMachine(2);

		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.TurnCrank();

		REQUIRE(mockMachine.GetState() == &mockMachine.GetHasQuarterState());
		REQUIRE(mockMachine.GetCoinsCount() == 1);
		REQUIRE(mockMachine.GetBallsCount() == 1);
	}
}

class NaiveGumballMachineMock : public naive::CGumballMachine
{
public:
	State GetState()
	{
		return naive::CGumballMachine::GetState();
	}

	unsigned GetCoinsCount()
	{
		return naive::CGumballMachine::GetCoinsCount();
	}

	unsigned GetBallsCount()
	{
		return naive::CGumballMachine::GetBallsCount();
	}
};

SCENARIO("testing NaiveGumballMachine soldOut state")
{
	NaiveGumballMachineMock mockMachine(0);

	REQUIRE(mockMachine.GetBallsCount() == 0);
	REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::SoldOut);

	GIVEN("a machine with 0 coins")
	{
		WHEN("ejecting quarter")
		{
			mockMachine.EjectQuarter();
			REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::SoldOut);
		}

		WHEN("inserting quarter")
		{
			mockMachine.InsertQuarter();
			REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::SoldOut);
		}

		WHEN("turnCranck quarter")
		{
			mockMachine.TurnCrank();
			REQUIRE(mockMachine.GetBallsCount() == 0);
			REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::SoldOut);
		}
	}
}

SCENARIO("testing NaiveGumballMachine noQuarterState state")
{
	NaiveGumballMachineMock mockMachine(3);

	REQUIRE(mockMachine.GetBallsCount() == 3);
	REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::NoQuarter);

	WHEN("ejecting quarter")
	{
		mockMachine.EjectQuarter();
		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::NoQuarter);
		REQUIRE(mockMachine.GetCoinsCount() == 0);
	}

	WHEN("inserting quarter")
	{
		mockMachine.InsertQuarter();
		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::HasQuarter);
		REQUIRE(mockMachine.GetCoinsCount() == 1);
	}

	WHEN("turnCranck quarter")
	{
		mockMachine.TurnCrank();
		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::NoQuarter);
		REQUIRE(mockMachine.GetCoinsCount() == 0);
	}
}

SCENARIO("testing NaiveGumballMachine haveQuarterState state")
{
	NaiveGumballMachineMock mockMachine(3);

	mockMachine.InsertQuarter();
	REQUIRE(mockMachine.GetCoinsCount() == 1);

	WHEN("ejecting quarter")
	{
		mockMachine.EjectQuarter();
		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::NoQuarter);
		REQUIRE(mockMachine.GetCoinsCount() == 0);
	}

	WHEN("inserting quarter")
	{
		mockMachine.InsertQuarter();
		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::HasQuarter);
		REQUIRE(mockMachine.GetCoinsCount() == 2);
	}

	WHEN("turnCranck quarter")
	{
		mockMachine.TurnCrank();
		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::NoQuarter);
		REQUIRE(mockMachine.GetCoinsCount() == 0);
	}

	WHEN("inserting quarter 5 times")
	{
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();

		REQUIRE(mockMachine.GetCoinsCount() == 5);
		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::HasQuarter);
	}

	WHEN("inserting quarter 6 times")
	{
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();

		REQUIRE(mockMachine.GetCoinsCount() == 5);
		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::HasQuarter);
	}
}

SCENARIO("dispense gumball NaiveGumballMachine")
{
	GIVEN("gumballMachine without gumballs in soldState")
	{
		NaiveGumballMachineMock mockMachine(1);

		mockMachine.InsertQuarter();
		mockMachine.TurnCrank();

		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::SoldOut);
		REQUIRE(mockMachine.GetBallsCount() == 0);
	}

	GIVEN("gumballMachine with gumballs in soldState with one coin")
	{
		NaiveGumballMachineMock mockMachine(2);

		mockMachine.InsertQuarter();
		mockMachine.TurnCrank();

		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::NoQuarter);
		REQUIRE(mockMachine.GetBallsCount() == 1);
	}

	GIVEN("gumballMachine with gumballs in soldState with two coins")
	{
		NaiveGumballMachineMock mockMachine(2);

		mockMachine.InsertQuarter();
		mockMachine.InsertQuarter();
		mockMachine.TurnCrank();

		REQUIRE(mockMachine.GetState() == naive::CGumballMachine::State::HasQuarter);
		REQUIRE(mockMachine.GetCoinsCount() == 1);
		REQUIRE(mockMachine.GetBallsCount() == 1);
	}
}