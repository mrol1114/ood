#pragma once

#include "../Shape/IShape.h"

class IShapes
{
public:
	virtual size_t GetShapeCount()const = 0;

	virtual IShapePtr const& GetShapeAtIndex(size_t index)const = 0;

	virtual void InsertShape(IShapePtr shape, std::optional<size_t> index) = 0;

	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IShapes() = default;
};