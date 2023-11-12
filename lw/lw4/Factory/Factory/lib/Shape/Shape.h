#pragma once

#include <iostream>

#include "./IShape.h"

class Shape : public IShape
{
public:
	Color GetColor()const override
	{
		return m_color;
	}

	void Draw(ICanvas& canvas)const override
	{
		canvas.SetColor(m_color);
		DrawShape(canvas);
	}

protected:
	Shape(Color color)
		: m_color(color)
	{
	}

	virtual void DrawShape(ICanvas& canvas)const = 0;

private:
	Color m_color;
};