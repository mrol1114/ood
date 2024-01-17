#pragma once

#include <stdexcept>

class CFrame
{
public:
	CFrame(double left = 0, double top = 0, double width = 0, double height = 0)
		: m_left(left)
		, m_top(top)
		, m_width(width)
		, m_height(height)
	{
		EnsurePassedParamNotNegative(width);
		EnsurePassedParamNotNegative(height);
	}

	double GetLeft()const
	{
		return m_left;
	}

	double GetTop()const
	{
		return m_top;
	}

	double GetWidth()const
	{
		return m_width;
	}

	double GetHeight()const
	{
		return m_height;
	}

private:
	static void EnsurePassedParamNotNegative(double value)
	{
		if (value < 0)
		{
			throw std::runtime_error("Passed frame param must not be negative");
		}
	}

	double m_left;
	double m_top;
	double m_width;
	double m_height;
};