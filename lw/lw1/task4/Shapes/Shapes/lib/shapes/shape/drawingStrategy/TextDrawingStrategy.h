#pragma once

#include <memory>
#include <iostream>

#include "./IDrawingStrategy.h"
#include "../../../canvas/Point.h"

class TextDrawingStrategy : public IDrawingStrategy
{
public:
	TextDrawingStrategy(Point leftTopPoint, double fontSize, const std::string& text)
	{
		if (fontSize < 0)
		{
			throw std::invalid_argument("Width should be more or equal to zero");
		}

		m_startPoint = leftTopPoint;
		m_fontSize = fontSize;
		m_text = text;
	}

	void Draw(ICanvas& canvas, const Color& c) const override
	{
		canvas.SetColor(c);
		canvas.DrawText(m_startPoint.x, m_startPoint.y, m_fontSize, m_text);
	}

	void Move(double dx, double dy) override
	{
		m_startPoint.x += dx;
		m_startPoint.y += dy;
	}

	virtual ShapeType GetType() const override
	{
		return ShapeType::Text;
	}

	std::string GetDrawParams() const override
	{
		return std::to_string(m_startPoint.x) + " " + std::to_string(m_startPoint.y) + " "
			+ std::to_string(m_fontSize) + " " + m_text;
	}

private:
	Point m_startPoint;
	std::string m_text;
	double m_fontSize;
};