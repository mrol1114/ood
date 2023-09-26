#pragma once

#include <memory>
#include <iostream>

#include "./IDrawingStrategy.h"
#include "../../../canvas/Point.h"

class CircleDrawingStrategy: public IDrawingStrategy
{
public:
	CircleDrawingStrategy(Point center, double radius)
	{
		if (radius < 0)
		{
			throw std::invalid_argument("Radius should be more or equal to zero");
		}

		m_center = center;
		m_radius = radius;
	}

	void Draw(ICanvas& canvas, const Color& c) const override
	{
		canvas.SetColor(c);
		canvas.DrawEllipse(m_center.x, m_center.y, m_radius, m_radius);
	}

	void Move(double dx, double dy) override
	{
		m_center.x += dx;
		m_center.y += dy;
	}

	virtual ShapeType GetType() const override
	{
		return ShapeType::Circle;
	}

	std::string GetDrawParams() const override
	{
		return std::to_string(m_center.x) + " "
			+ std::to_string(m_center.y) + " " + std::to_string(m_radius);
	}

private:
	Point m_center;
	double m_radius;
};