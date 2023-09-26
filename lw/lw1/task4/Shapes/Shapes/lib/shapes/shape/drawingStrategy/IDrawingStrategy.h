#pragma once

#include <memory>

#include "../../../canvas/ICanvas.h"
#include "../ShapeType.h"

class IDrawingStrategy
{
public:
	virtual ~IDrawingStrategy() = default;
	virtual void Draw(ICanvas& canvas, const Color& c) const = 0;
	virtual void Move(double dx, double dy) = 0;
	virtual ShapeType GetType() const = 0;
	virtual std::string GetDrawParams() const = 0;
};