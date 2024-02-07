#pragma once

#include <memory>

#include "../IShape.h"

class CShapeFactory
{
public:
	static std::shared_ptr<IShape> CreateShape(ShapeType type, CFrame frame);
};