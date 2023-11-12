#pragma once

#include "./Shape.h"

class CTriangle final : public Shape
{
public:
	CTriangle(Point v1, Point v2, Point v3, Color color)
		: Shape(color)
		, m_v1(v1)
		, m_v2(v2)
		, m_v3(v3)
	{
	}

	Point GetVertex1()const
	{
		return m_v1;
	}

	Point GetVertex2()const
	{
		return m_v2;
	}

	Point GetVertex3()const
	{
		return m_v3;
	}

private:
	void DrawShape(ICanvas& canvas)const override
	{
		canvas.DrawLine(m_v1, m_v2);
		canvas.DrawLine(m_v2, m_v3);
		canvas.DrawLine(m_v3, m_v1);
	}

	Point m_v1;
	Point m_v2;
	Point m_v3;
};