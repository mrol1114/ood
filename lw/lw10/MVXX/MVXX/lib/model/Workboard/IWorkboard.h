#pragma once

#include "../Picture/IPicture.h"

class IWorkboard
{
public:
	virtual void HandleClick(double x, double y) = 0;

	virtual void HandleDrag(double x, double y) = 0;

	virtual void AddShapeToDefaultPosition(ShapeType type) = 0;

	virtual IPicture* GetPicture()const = 0;

	virtual ~IWorkboard() = default;
};