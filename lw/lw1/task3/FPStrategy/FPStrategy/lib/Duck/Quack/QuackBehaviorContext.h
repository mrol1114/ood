#pragma once

#include <functional>

using QuackStrategy = std::function<void()>;

class QuackBehaviorContext
{
public:
	void PerformOperation()
	{
		if (m_strategy)
		{
			m_strategy();
		}
		return;
	}

	void SetStrategy(const QuackStrategy& s)
	{
		m_strategy = s;
	}

private:
	QuackStrategy m_strategy;
};