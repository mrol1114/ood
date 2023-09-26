#pragma once

#include <memory>
#include <iostream>

#include "./IShapeStrategy.h"
#include "../../../canvas/Point.h"

class RectangleShapeStrategy : public IShapeStrategy
{
public:
	RectangleShapeStrategy(Point leftTopPoint, double width, double height)
	{
		if (width < 0)
		{
			throw std::invalid_argument("Width should be more or equal to zero");
		}
		if (height < 0)
		{
			throw std::invalid_argument("Height should be more or equal to zero");
		}

		m_p1 = leftTopPoint;
		m_p2 = {leftTopPoint.x + width, leftTopPoint.y};
		m_p3 = {leftTopPoint.x + width, leftTopPoint.y + height};
		m_p4 = {leftTopPoint.x, leftTopPoint.y + height};
	}

	void Draw(ICanvas& canvas, const Color& c) const override
	{
		canvas.SetColor(c);
		canvas.MoveTo(m_p1.x, m_p1.y);
		canvas.LineTo(m_p2.x, m_p2.y);
		canvas.MoveTo(m_p2.x, m_p2.y);
		canvas.LineTo(m_p3.x, m_p3.y);
		canvas.MoveTo(m_p3.x, m_p3.y);
		canvas.LineTo(m_p4.x, m_p4.y);
		canvas.MoveTo(m_p4.x, m_p4.y);
		canvas.LineTo(m_p1.x, m_p1.y);
	}

	void Move(double dx, double dy) override
	{
		m_p1.x += dx;
		m_p1.y += dy;
		m_p2.x += dx;
		m_p2.y += dy;
		m_p3.x += dx;
		m_p3.y += dy;
		m_p4.x += dx;
		m_p4.y += dy;
	}

	virtual ShapeType GetType() const override
	{
		return ShapeType::Rectangle;
	}

	std::string GetDrawInfo() const override
	{
		return std::to_string(m_p1.x) + " "
			+ std::to_string(m_p1.y) + " "
			+ std::to_string(m_p2.x - m_p1.x) + " " + std::to_string(m_p3.y - m_p2.y);
	}

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
	Point m_p4;
};