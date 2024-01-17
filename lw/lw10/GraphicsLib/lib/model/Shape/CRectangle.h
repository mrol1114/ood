#pragma once

#include "CShape.h"

class CRectangle : public CShape
{
public:
	ShapeType GetType()const override
	{
		return ShapeType::Rectangle;
	}

	bool IsShapeIncludePoint(double x, double y)const override
	{
		return m_frame.GetLeft() <= x && m_frame.GetLeft() + m_frame.GetWidth() >= x
			&& m_frame.GetTop() <= y && m_frame.GetTop() + m_frame.GetTop() >= y;
	}
};