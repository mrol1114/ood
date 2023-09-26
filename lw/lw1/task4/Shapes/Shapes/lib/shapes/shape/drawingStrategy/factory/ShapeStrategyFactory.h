#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "../CircleShapeStrategy.h"
#include "../RectangleShapeStrategy.h"
#include "../TriangleShapeStrategy.h"
#include "../LineShapeStrategy.h"
#include "../TextShapeStrategy.h"

class ShapeStrategyFactory
{
public:
	std::unique_ptr<IShapeStrategy> Create(ShapeType shapeType, std::istream& input)
	{
		switch (shapeType)
		{
		case ShapeType::Triangle:
		{
			double x1, x2, x3, y1, y2, y3;
			input >> x1 >> x2 >> x3 >> y1 >> y2 >> y3;

			return std::make_unique<TriangleShapeStrategy>(Point{x1, y1}, Point{x2, y2}, Point{x3, y3});
		}
		case ShapeType::Rectangle:
		{
			double left, top, width, height;
			input >> left >> top >> width >> height;

			return std::make_unique<RectangleShapeStrategy>(Point{left, top}, width, height);
		}
		case ShapeType::Text:
		{
			double left, top, fontSize;
			std::string text;
			input >> left >> top >> fontSize >> text;

			return std::make_unique<TextShapeStrategy>(Point{left, top}, fontSize, text);
		}
		case ShapeType::Line:
		{
			double x1, x2, y1, y2;
			input >> x1 >> x2 >> y1 >> y2;

			return std::make_unique<LineShapeStrategy>(Point{x1, y1}, Point{x2, y2});
		}
		case ShapeType::Circle:
		{
			double left, top, radius;
			input >> left >> top >> radius;

			return std::make_unique<CircleShapeStrategy>(Point{left, top}, radius);
		}
		default:
			throw std::runtime_error("Error! Type does not have realization");
		}
	}
};