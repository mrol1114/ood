#include "CRectangle.h"

CRectangle::CRectangle(CFrame frame)
	: CShape(frame)
{
}

ShapeType CRectangle::GetType()const
{
	return ShapeType::Rectangle;
}

bool CRectangle::IsShapeIncludePoint(double x, double y)const
{
	return m_frame.GetLeft() <= x && m_frame.GetLeft() + m_frame.GetWidth() >= x
		&& m_frame.GetTop() <= y && m_frame.GetTop() + m_frame.GetHeight() >= y;
}