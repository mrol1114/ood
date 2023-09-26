#pragma once

#include <memory>

#include "../../../canvas/ICanvas.h"
#include "../ShapeType.h"

class IShapeStrategy
{
public:
	virtual ~IShapeStrategy() = default;
	virtual void Draw(ICanvas& canvas, const Color& c) const = 0;
	virtual void Move(double dx, double dy) = 0;
	virtual ShapeType GetType() const = 0;
	virtual std::string GetDrawInfo() const = 0;
};