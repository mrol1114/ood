#pragma once

#include <cmath>

#include "CShape.h"

class CEllipse : public CShape
{
public:
	ShapeType GetType()const override
	{
		return ShapeType::Ellipse;
	}

	bool IsShapeIncludePoint(double x, double y)const override
	{
		return std::pow((x - m_frame.GetWidth() / 2 - m_frame.GetLeft()), 2) 
			/ std::pow((m_frame.GetWidth() / 2), 2)
			+ std::pow((y - m_frame.GetHeight() / 2 - m_frame.GetTop()), 2)
			/ std::pow((m_frame.GetHeight() / 2), 2)
			<= 1;
	}
};