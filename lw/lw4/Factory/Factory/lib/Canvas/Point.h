#pragma once

struct Point
{
	double x = 0;
	double y = 0;

	auto operator==(const Point& other)const
	{
		return x == other.x && y == other.y;
	}
};