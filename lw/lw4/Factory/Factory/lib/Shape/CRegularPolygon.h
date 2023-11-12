#pragma once

#define _USE_MATH_DEFINES

#include <string>
#include <math.h>

#include "./Shape.h"

class CRegularPolygon final : public Shape
{
public:
	CRegularPolygon(Point center, double radius, unsigned int vertexCount, Color color)
		: Shape(color)
	{
		if (radius <= 0)
		{
			throw std::logic_error("Radius must be greater than 0");
		}
		if (vertexCount <= m_MIN_VERTEX_COUNT)
		{
			throw std::logic_error("Vertex count must be greater than "
				+ std::to_string(m_MIN_VERTEX_COUNT));
		}

		m_radius = radius;
		m_center = center;
		m_vertexCount = vertexCount;
	}

	Point GetCenter()const
	{
		return m_center;
	}

	double GetRadius()const
	{
		return m_radius;
	}

	unsigned int GetVertexCount()const
	{
		return m_vertexCount;
	}

private:
	void DrawShape(ICanvas& canvas)const override
	{
		double curAngle = 0;
		double angleIncrement = static_cast<double>(360) / m_vertexCount;
		Point firstVertex = { 
			m_center.x + m_radius * std::cos(ConvertDegreesToRadians(curAngle)),
			m_center.y + m_radius * std::sin(ConvertDegreesToRadians(curAngle))
		};
		Point lastVertex = firstVertex;

		for (unsigned int curVertexCount = 0; curVertexCount < m_vertexCount - 1; curVertexCount++)
		{
			curAngle += angleIncrement;

			Point nextVertex;
			nextVertex.x = m_center.x + m_radius * std::cos(ConvertDegreesToRadians(curAngle));
			nextVertex.y = m_center.y + m_radius * std::sin(ConvertDegreesToRadians(curAngle));

			canvas.DrawLine(lastVertex, nextVertex);
			lastVertex = nextVertex;
		}

		canvas.DrawLine(lastVertex, firstVertex);
	}

	double ConvertDegreesToRadians(double degrees)const
	{
		return degrees / 180 * M_PI;
	}

	const unsigned int m_MIN_VERTEX_COUNT = 2;
	Point m_center;
	double m_radius;
	unsigned int m_vertexCount;
};