#pragma once

#include "./Shape.h"

class CEllipse final : public Shape
{
public:
	CEllipse(Point center, double width, double height, Color color)
		: Shape(color)
	{
		if (width <= 0 || height <= 0)
		{
			throw std::logic_error("Width and height must be greater than 0");
		}

		m_center = center;
		m_width = width;
		m_height = height;
	}

	Point GetCenter()const
	{
		return m_center;
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
	void DrawShape(ICanvas& canvas)const override
	{
		canvas.DrawEllipse(m_center.x, m_center.y, m_width, m_height);
	}

	Point m_center;
	double m_width;
	double m_height;
};