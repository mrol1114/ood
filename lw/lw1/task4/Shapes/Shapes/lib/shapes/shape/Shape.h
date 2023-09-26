#pragma once

#include <memory>

#include "./drawingStrategy/IShapeStrategy.h"
#include "../../canvas/ICanvas.h"
#include "./ShapeType.h"

class Shape
{
public:
	Shape(std::unique_ptr<IShapeStrategy>&& drawingStrategy, const Color& color)
		: m_drawingStrategy(std::move(drawingStrategy))
		, m_color(color)
	{
	}

	void Draw(ICanvas& canvas) const
	{
		m_drawingStrategy->Draw(canvas, m_color);
	}

	void Move(double dx, double dy) const
	{
		m_drawingStrategy->Move(dx, dy);
	}

	std::string GetDrawInfo() const
	{
		return m_drawingStrategy->GetDrawInfo();
	}

	Color GetColor()
	{
		return m_color;
	}

	ShapeType GetType()
	{
		return m_drawingStrategy->GetType();
	}

	void SetColor(const Color& c)
	{
		m_color = c;
	}

	void SetDrawingStrategy(std::unique_ptr<IShapeStrategy>&& drawingStrategy)
	{
		m_drawingStrategy = std::move(drawingStrategy);
	}

private:
	std::unique_ptr<IShapeStrategy> m_drawingStrategy;
	Color m_color;
};