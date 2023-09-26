#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "../CircleDrawingStrategy.h"
#include "../RectangleDrawingStrategy.h"
#include "../TriangleDrawingStrategy.h"
#include "../LineDrawingStrategy.h"
#include "../TextDrawingStrategy.h"

class DrawingStrategyFactory
{
public:
	std::unique_ptr<IDrawingStrategy> Create(ShapeType shapeType, std::istream& input)
	{
		switch (shapeType)
		{
		case ShapeType::Triangle:
		{
			double x1, x2, x3, y1, y2, y3;
			input >> x1 >> x2 >> x3 >> y1 >> y2 >> y3;

			return std::make_unique<TriangleDrawingStrategy>(Point{x1, y1}, Point{x2, y2}, Point{x3, y3});
		}
		case ShapeType::Rectangle:
		{
			double left, top, width, height;
			input >> left >> top >> width >> height;

			return std::make_unique<RectangleDrawingStrategy>(Point{left, top}, width, height);
		}
		case ShapeType::Text:
		{
			double left, top, fontSize;
			std::string text;
			input >> left >> top >> fontSize >> text;

			return std::make_unique<TextDrawingStrategy>(Point{left, top}, fontSize, text);
		}
		case ShapeType::Line:
		{
			double x1, x2, y1, y2;
			input >> x1 >> x2 >> y1 >> y2;

			return std::make_unique<LineDrawingStrategy>(Point{x1, y1}, Point{x2, y2});
		}
		case ShapeType::Circle:
		{
			double left, top, radius;
			input >> left >> top >> radius;

			return std::make_unique<CircleDrawingStrategy>(Point{left, top}, radius);
		}
		default:
			throw std::runtime_error("Error! Type does not have realization");
		}
	}
};