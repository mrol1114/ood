#pragma once

#include <functional>

using DanceStrategy = std::function<void()>;

class DanceBehaviorContext
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

	void SetStrategy(const DanceStrategy& s)
	{
		m_strategy = s;
	}

private:
	DanceStrategy m_strategy;
};