#include "./CFrame.h"

CFrame::CFrame(double left, double top, double width, double height)
	: m_left(left)
	, m_top(top)
	, m_width(width)
	, m_height(height)
{
	EnsurePassedParamNotNegative(width);
	EnsurePassedParamNotNegative(height);
}

double CFrame::GetLeft()const
{
	return m_left;
}

double CFrame::GetTop()const
{
	return m_top;
}

double CFrame::GetWidth()const
{
	return m_width;
}

double CFrame::GetHeight()const
{
	return m_height;
}

void CFrame::EnsurePassedParamNotNegative(double value)
{
	if (value < 0)
	{
		throw std::runtime_error("Passed frame param must not be negative");
	}
}