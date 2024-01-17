#pragma once

#include <string>

#include "./RGBA.h"
#include "./Point.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void BeginPath() = 0;

	virtual void EndPath() = 0;

	virtual void SetLineColor(RGBA color) = 0;

	virtual void SetFillColor(RGBA color) = 0;

	virtual void SetLineWidth(double lineWidth) = 0;

	virtual void MoveTo(Point to) = 0;

	virtual void LineTo(Point to) = 0;

	virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;

	virtual void Clear() = 0;
};