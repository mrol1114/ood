#pragma once

#include <functional>

using FlyStrategy = std::function<void(int countFlights)>;

class FlyBehaviorContext
{
public:
	void PerformOperation()
	{
		if (m_strategy)
		{
			m_countFlights++;
			m_strategy(m_countFlights);
		}
		return;
	}

	void SetStrategy(const FlyStrategy& s)
	{
		m_strategy = s;
		m_countFlights = 0;
	}

private:
	FlyStrategy m_strategy;
	unsigned int m_countFlights = 0;
};