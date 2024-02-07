#pragma once

#include <stdexcept>

class CFrame
{
public:
	CFrame(double left = 0, double top = 0, double width = 0, double height = 0);

	double GetLeft()const;

	double GetTop()const;

	double GetWidth()const;

	double GetHeight()const;

private:
	static void EnsurePassedParamNotNegative(double value);

	double m_left;
	double m_top;
	double m_width;
	double m_height;
};