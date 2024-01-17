#pragma once

#include <string>
#include <vector>

struct Shape
{
	Shape(std::string type, double left, double top, double width, double height)
		: type(type)
		, left(left)
		, top(top)
		, width(width)
		, height(height)
	{
	}

	std::string type;
	double left;
	double top;
	double width;
	double height;
};

struct Shapes
{
	std::vector<Shape> shapes = {};
	Shape* currShape = nullptr;
};