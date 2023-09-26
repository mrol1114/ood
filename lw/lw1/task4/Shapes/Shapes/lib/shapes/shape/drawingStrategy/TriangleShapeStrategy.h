#pragma once

#include <memory>

#include "./IShapeStrategy.h"
#include "../../../canvas/Point.h"

class TriangleShapeStrategy : public IShapeStrategy
{
public:
	TriangleShapeStrategy(Point p1, Point p2, Point p3)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
	{
	}

	void Draw(ICanvas& canvas, const Color& c) const override
	{
		canvas.SetColor(c);
		canvas.MoveTo(m_p1.x, m_p1.y);
		canvas.LineTo(m_p2.x, m_p2.y);
		canvas.MoveTo(m_p2.x, m_p2.y);
		canvas.LineTo(m_p3.x, m_p3.y);
		canvas.MoveTo(m_p3.x, m_p3.y);
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
	}

	virtual ShapeType GetType() const override
	{
		return ShapeType::Triangle;
	}

	std::string GetDrawInfo() const override
	{
		return std::to_string(m_p1.x) + " " + std::to_string(m_p1.y) + " "
			+ std::to_string(m_p2.x) + " " + std::to_string(m_p2.y) + " "
			+ std::to_string(m_p3.x) + " " + std::to_string(m_p3.y);
	}

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};