#pragma once

#include <functional>

#include "../ShapeGroup/IShapeGroup.h"

using CShapeGroupEnumeratorCallback = std::function<void(IShape&)>;

class IShapeGroupEnumerator
{
public:
	virtual void EnumerateAll(CShapeGroupEnumeratorCallback callback) = 0;

	virtual ~IShapeGroupEnumerator() = default;
};