#pragma once

#include "../Picture/IPicture.h"
#include "../Picture/CPictureIterator.h"

class IWorkboard
{
public:
	virtual void HandleClick(double x, double y) = 0;
	virtual void HandleDrag(double x, double y) = 0;
	virtual void FinishDrag() = 0;

	virtual void AddShape(ShapeType type) = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;

	virtual CPictureIterator GetShapesIterator()const = 0;
	virtual std::shared_ptr<IShape> GetCurrShape()const = 0;

	virtual ~IWorkboard() = default;
};