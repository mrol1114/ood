#pragma once

#include <memory>

#include "../Shape/IShape.h"
#include "./CPictureIterator.h"

class IPicture
{
public:
	virtual std::shared_ptr<IShape> GetCurrShape()const = 0;
	virtual void SetCurrShape(std::shared_ptr<IShape> shape) = 0;

	virtual void AddShape(CFrame frame, ShapeType type) = 0;

	virtual std::shared_ptr<IShape> GetShapeByCoors(double x, double y)const = 0;

	virtual void ChangePositionOfCurrShape(double x, double y) = 0;
	virtual void ChangeSizeOfCurrShape(double x, double y, double width, double height) = 0;

	virtual CPictureIterator GetIterator() = 0;

	virtual ~IPicture() = default;
};