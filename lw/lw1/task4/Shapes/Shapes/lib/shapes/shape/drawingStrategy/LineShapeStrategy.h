#pragma once

#include "./IShapeStrategy.h"
#include "../../../canvas/Point.h"

class LineShapeStrategy : public IShapeStrategy
{
public:
	LineShapeStrategy(Point p1, Point p2)
		: m_p1(p1)
		, m_p2(p2)
	{
	}

	void Draw(ICanvas& canvas, const Color& c) const override
	{
		canvas.SetColor(c);
		canvas.MoveTo(m_p1.x, m_p1.y);
		canvas.LineTo(m_p2.x, m_p2.y);
	}

	void Move(double dx, double dy) override
	{
		m_p1.x += dx;
		m_p1.y += dy;
		m_p2.x += dx;
		m_p2.y += dy;
	}

	virtual ShapeType GetType() const override
	{
		return ShapeType::Line;
	}

	std::string GetDrawInfo() const override
	{
		return std::to_string(m_p1.x) + " " + std::to_string(m_p1.y) + " "
			+ std::to_string(m_p2.x) + " " + std::to_string(m_p2.y);
	}

private:
	Point m_p1;
	Point m_p2;
};