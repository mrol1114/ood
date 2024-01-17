#pragma once

#include "./CFrame.h"
#include "./ShapeType.h"

class IShape
{
public:
	virtual CFrame GetFrame()const = 0;

	virtual void SetFrame(CFrame frame) = 0;

	virtual ShapeType GetType()const = 0;

	virtual bool IsShapeIncludePoint(double x, double y)const = 0;
};