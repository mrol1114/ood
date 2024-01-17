#pragma once

#include "CShape.h"

class CTriangle : public CShape
{
public:
	ShapeType GetType()const override
	{
		return ShapeType::Triangle;
	}

	bool IsShapeIncludePoint(double x, double y)const override
	{
		double x1 = m_frame.GetLeft();
		double y1 = m_frame.GetLeft() + m_frame.GetHeight();
		double x2 = m_frame.GetLeft() + m_frame.GetWidth() / 2;
		double y2 = m_frame.GetHeight();
		double x3 = m_frame.GetLeft() + m_frame.GetWidth();
		double y3 = m_frame.GetTop() + m_frame.GetHeight();

		double A = CalculateTriangleArea(x1, y1, x2, y2, x3, y3);
		double A1 = CalculateTriangleArea(x, y, x2, y2, x3, y3);
		double A2 = CalculateTriangleArea(x1, y1, x, y, x3, y3);
		double A3 = CalculateTriangleArea(x1, y1, x2, y2, x, y);

		return A == A1 + A2 + A3;
	}

private:
	static double CalculateTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3)
	{
		return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
	}
};