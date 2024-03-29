#pragma once

#include <iostream>
#include <format>
#include <stdexcept>

namespace naive
{
	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,		// ������ �����������
			NoQuarter,		// ��� �������
			HasQuarter,		// ���� �������
			Sold,			// ������� ������
		};

		CGumballMachine(unsigned count)
			: m_ballsCount(count)
			, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		{
		}

		void InsertQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You can't insert a quarter, the machine is sold out\n";
				break;
			case State::NoQuarter:
				DoInsertQuarter();
				break;
			case State::HasQuarter:
				DoInsertQuarter();
				cout << "You can't insert another quarter\n";
				break;
			case State::Sold:
				cout << "Please wait, we're already giving you a gumball\n";
				break;
			}
		}

		void EjectQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::HasQuarter:
				cout << "Quarter returned\n";
				m_coinsCount = 0;
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				cout << "You haven't inserted a quarter\n";
				break;
			case State::Sold:
				cout << "Sorry you already turned the crank\n";
				break;
			case State::SoldOut:
				if (m_coinsCount > 0)
				{
					m_coinsCount = 0;
					cout << "Quarter returned\n";
				}
				else
				{
					cout << "You can't eject, you haven't inserted a quarter yet\n";
				}
				break;
			}
		}

		void TurnCrank()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You turned but there's no gumballs\n";
				break;
			case State::NoQuarter:
				cout << "You turned but there's no quarter\n";
				break;
			case State::HasQuarter:
				cout << "You turned...\n";
				m_state = State::Sold;
				m_coinsCount--;
				Dispense();
				break;
			case State::Sold:
				cout << "Turning twice doesn't get you another gumball\n";
				break;
			}
		}

		void Refill(unsigned numBalls)
		{
			m_ballsCount = numBalls;
			m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
		}

		std::string ToString()const
		{
			std::string state =
				(m_state == State::SoldOut) ? "sold out" :
				(m_state == State::NoQuarter) ? "waiting for quarter" :
				(m_state == State::HasQuarter) ? "waiting for turn of crank"
				: "delivering a gumball";

			return std::format(R"(Mighty Gumball, Inc.
				C++ - enabled Standing Gumball Model #2016
				Inventory: {} gumball {}
				Machine is {})", m_ballsCount, m_ballsCount != 1 ? "s" : "", state);
		}

	protected:
		State GetState()
		{
			return m_state;
		}

		unsigned GetCoinsCount()
		{
			return m_coinsCount;
		}

		unsigned GetBallsCount()
		{
			return m_ballsCount;
		}

	private:
		void Dispense()
		{
			using namespace std;
			switch (m_state)
			{
			case State::Sold:
				cout << "A gumball comes rolling out the slot\n";
				--m_ballsCount;
				if (m_ballsCount == 0)
				{
					cout << "Oops, out of gumballs\n";
					m_state = State::SoldOut;
				}
				else
				{
					m_state = m_coinsCount > 0 ? State::HasQuarter : State::NoQuarter;
				}
				break;
			case State::NoQuarter:
				cout << "You need to pay first\n";
				break;
			case State::SoldOut:
			case State::HasQuarter:
				cout << "No gumball dispensed\n";
				break;
			}
		}

		void DoInsertQuarter()
		{
			if (m_coinsCount + 1 > m_MAX_COINS_COUNT)
			{
				std::cout << std::format("Machine can take no more then {} coins", m_MAX_COINS_COUNT);
			}
			else
			{
				m_coinsCount++;
				std::cout << "You inserted a quarter\n";
				m_state = State::HasQuarter;
			}
		}

		static const unsigned m_MAX_COINS_COUNT = 5;
		unsigned m_ballsCount;	// ���������� �������
		unsigned m_coinsCount = 0;	// ���������� �������
		State m_state = State::SoldOut;
	};
}