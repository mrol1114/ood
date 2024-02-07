#include "./CKeyPoint.h"

CKeyPoint::CKeyPoint(CFrame frame)
	: m_frame(frame)
{
}

bool CKeyPoint::IsShapeIncludePoint(double x, double y)const
{
	return std::pow((x - m_frame.GetWidth() / 2 - m_frame.GetLeft()), 2)
		/ std::pow((m_frame.GetWidth() / 2), 2)
		+ std::pow((y - m_frame.GetHeight() / 2 - m_frame.GetTop()), 2)
		/ std::pow((m_frame.GetHeight() / 2), 2)
		<= 1;
}

CFrame CKeyPoint::GetFrame()const
{
	return m_frame;
}

void CKeyPoint::SetFrame(CFrame frame)
{
	m_frame = frame;
}