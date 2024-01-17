#pragma once

#include <cmath>
#include "../Shape/CFrame.h"

class KeyPoint
{
public:
	KeyPoint(CFrame frame)
		: m_frame(frame)
	{
	}

	bool IsShapeIncludePoint(double x, double y)const
	{
		return std::pow((x - m_frame.GetWidth() / 2 - m_frame.GetLeft()), 2)
			/ std::pow((m_frame.GetWidth() / 2), 2)
			+ std::pow((y - m_frame.GetHeight() / 2 - m_frame.GetTop()), 2)
			/ std::pow((m_frame.GetHeight() / 2), 2)
			<= 1;
	}

	CFrame GetFrame()const
	{
		return m_frame;
	}

	void SetFrame(CFrame frame)
	{
		m_frame = frame;
	}

private:
	CFrame m_frame;
};