#include "./CEllipse.h"

CEllipse::CEllipse(CFrame frame)
	: CShape(frame)
{
}

ShapeType CEllipse::GetType()const
{
	return ShapeType::Ellipse;
}

bool CEllipse::IsShapeIncludePoint(double x, double y)const
{
	return std::pow((x - m_frame.GetWidth() / 2 - m_frame.GetLeft()), 2)
		/ std::pow((m_frame.GetWidth() / 2), 2)
		+ std::pow((y - m_frame.GetHeight() / 2 - m_frame.GetTop()), 2)
		/ std::pow((m_frame.GetHeight() / 2), 2)
		<= 1;
}