#pragma once

#include "CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(CFrame frame);

	ShapeType GetType()const override;

	bool IsShapeIncludePoint(double x, double y)const override;
};