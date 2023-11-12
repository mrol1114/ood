#pragma once

#include <memory>
#include <vector>

#include "../Shape/IShape.h"

using Shapes = std::vector<ShapePtr>;

class PictureDraft
{
public:
	const Shapes& GetShapes()const
	{
		return m_shapes;
	}

	void Addshape(ShapePtr&& shape)
	{
		m_shapes.push_back(std::move(shape));
	}

private:
	Shapes m_shapes = {};
};