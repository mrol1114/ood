#pragma once

#include <memory>

#include "../Canvas/ICanvas.h"
#include "../Canvas/Color.h"

class IShape
{
public:
	virtual ~IShape() = default;

	virtual void Draw(ICanvas& canvas)const = 0;

	virtual Color GetColor()const = 0;

	virtual bool operator==(const IShape&)const = default;
};

using ShapePtr = std::unique_ptr<IShape>;