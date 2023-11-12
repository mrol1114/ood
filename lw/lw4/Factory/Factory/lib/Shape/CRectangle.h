#pragma once

#include "./Shape.h"

class CRectangle final : public Shape
{
public:
	CRectangle(Point leftTop, double width, double height, Color color)
		: Shape(color)
	{
		if (width <= 0 || height <= 0)
		{
			throw std::logic_error("Width and height must be greater than 0");
		}

		m_leftTop = leftTop;
		m_bottomRight.x = leftTop.x + width;
		m_bottomRight.y = leftTop.y + height;
	}

	Point GetLeftTop()const
	{
		return m_leftTop;
	}

	Point GetBottomRight()const
	{
		return m_bottomRight;
	}

private:
	void DrawShape(ICanvas& canvas)const override
	{
		canvas.DrawLine(m_leftTop, { m_bottomRight.x, m_leftTop.y });
		canvas.DrawLine({ m_bottomRight.x, m_leftTop.y }, m_bottomRight);
		canvas.DrawLine(m_bottomRight, { m_leftTop.x, m_bottomRight.y });
		canvas.DrawLine({ m_leftTop.x, m_bottomRight.y }, m_leftTop);
	}

	Point m_leftTop;
	Point m_bottomRight;
};