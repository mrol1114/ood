#pragma once

#include <string>
#include <memory>

#include "../IShape.h"

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual ShapePtr CreateShape(const std::string& shapeDescr) = 0;
};

using ShapeFactoryPtr = std::unique_ptr<IShapeFactory>;