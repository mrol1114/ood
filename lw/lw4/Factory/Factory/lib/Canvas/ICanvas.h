#pragma once

#include "./Color.h"
#include "./Point.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetColor(Color c) = 0;

	virtual void DrawLine(Point from, Point to) = 0;

	virtual void DrawEllipse(double cx, double cy, double width, double height) = 0;
};