#pragma once

#include <vector>

#include "../Shape/IShapes.h"

class ISlide : public IShapes
{
public:
	virtual void CreateGroup(const std::vector<size_t>& slideIndexes) = 0;

	virtual void Ungroup(size_t groupIndex) = 0;

	virtual ~ISlide() = default;
};