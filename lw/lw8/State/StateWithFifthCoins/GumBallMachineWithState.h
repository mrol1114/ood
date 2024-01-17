#pragma once
#include <iostream>
#include <format>

namespace with_state
{
	class IState
	{
	public:
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual std::string ToString()const = 0;
		virtual ~IState() = default;
	};

	class IGumballMachine
	{
	public:
		virtual void ReleaseBall() = 0;
		virtual unsigned GetBallsCount()const = 0;

		virtual void IncreaseCoinsCount() = 0;
		virtual void DecreaseCoinsCount() = 0;
		virtual unsigned GetCoinsCount()const = 0;
		virtual bool CanIncreaseCoinsCount()const = 0;
		virtual void EmptyCoinsCount() = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;

		virtual ~IGumballMachine() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}
		void InsertQuarter() override
		{
			std::cout << "Please wait, we're already giving you a gumball\n";
		}
		void EjectQuarter() override
		{
			std::cout << "Sorry you already turned the crank\n";
		}
		void TurnCrank() override
		{
			std::cout << "Turning twice doesn't get you another gumball\n";
		}
		void Dispense() override
		{
			// последний шарик бесплатно
			m_gumballMachine.ReleaseBall();
			if (m_gumballMachine.GetBallsCount() == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_gumballMachine.SetSoldOutState();
			}
			else
			{
				m_gumballMachine.DecreaseCoinsCount();
				m_gumballMachine.GetCoinsCount() != 0
					? m_gumballMachine.SetHasQuarterState()
					: m_gumballMachine.SetNoQuarterState();
			}
		}
		std::string ToString() const override
		{
			return "delivering a gumball";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You can't insert a quarter, the machine is sold out\n";
		}
		void EjectQuarter() override
		{
			if (m_gumballMachine.GetCoinsCount() > 0)
			{
				m_gumballMachine.EmptyCoinsCount();
				std::cout << "Quarter returned\n";
			}
			else
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs\n";
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		std::string ToString() const override
		{
			return "sold out";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			if (m_gumballMachine.CanIncreaseCoinsCount())
			{
				m_gumballMachine.IncreaseCoinsCount();
				std::cout << "You inserted a quarter\n";
			}
			else
			{
				std::cout << "You can't insert another quarter\n";
			}
		}
		void EjectQuarter() override
		{
			std::cout << "Quarter returned\n";
			m_gumballMachine.EmptyCoinsCount();
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			std::cout << "You turned...\n";
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You inserted a quarter\n";
			m_gumballMachine.IncreaseCoinsCount();
			m_gumballMachine.SetHasQuarterState();
		}
		void EjectQuarter() override
		{
			std::cout << "You haven't inserted a quarter\n";
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no quarter\n";
		}
		void Dispense() override
		{
			std::cout << "You need to pay first\n";
		}
		std::string ToString() const override
		{
			return "waiting for quarter";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	// приватное наследование
	class CGumballMachine : public IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls)
			: m_soldState(*this)
			, m_soldOutState(*this)
			, m_noQuarterState(*this)
			, m_hasQuarterState(*this)
			, m_state(&m_soldOutState)
			, m_ballsCount(numBalls)
		{
			if (m_ballsCount > 0)
			{
				m_state = &m_noQuarterState;
			}
		}
		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}
		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}
		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}
		std::string ToString()const
		{
			return std::format(R"(Mighty Gumball, Inc.
				C++ - enabled Standing Gumball Model #2016
				Inventory: {} gumball {}
				Machine is {})", m_ballsCount, m_ballsCount != 1 ? "s" : "", m_state->ToString());
		}

	protected:
		unsigned GetBallsCount() const override
		{
			return m_ballsCount;
		}
		unsigned GetCoinsCount() const override
		{
			return m_coinsCount;
		}
		void IncreaseCoinsCount() override
		{
			if (m_coinsCount + 1 > m_MAX_COINS_COUNT)
			{
				std::cout << std::format("Machine can take no more then {} coins", m_MAX_COINS_COUNT);
			}
			else
			{
				m_coinsCount++;
			}
		}
		void DecreaseCoinsCount() override
		{
			m_coinsCount--;
		}
		bool CanIncreaseCoinsCount() const override
		{
			return m_coinsCount + 1 <= m_MAX_COINS_COUNT;
		}
		void EmptyCoinsCount() override
		{
			m_coinsCount = 0;
		}
		void ReleaseBall() override
		{
			if (m_ballsCount != 0)
			{
				std::cout << "A gumball comes rolling out the slot...\n";
				--m_ballsCount;
			}
		}
		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}
		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}
		void SetSoldState() override
		{
			m_state = &m_soldState;
		}
		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}
		CSoldOutState const& GetSoldOutState()
		{
			return m_soldOutState;
		}
		CNoQuarterState const& GetNoQuarterState()
		{
			return m_noQuarterState;
		}
		CSoldState const& GetSoldState()
		{
			return m_soldState;
		}
		CHasQuarterState const& GetHasQuarterState()
		{
			return m_hasQuarterState;
		}
		const IState* GetState()
		{
			return m_state;
		}

	private:
		static const unsigned m_MAX_COINS_COUNT = 5;

		unsigned m_ballsCount = 0;
		unsigned m_coinsCount = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState* m_state;
	};
}