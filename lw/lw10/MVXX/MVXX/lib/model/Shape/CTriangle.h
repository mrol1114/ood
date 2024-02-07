#pragma once

#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(CFrame frame);

	ShapeType GetType()const override;

	bool IsShapeIncludePoint(double x, double y)const override;
};