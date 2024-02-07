#pragma once

#include <cmath>

#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(CFrame frame);

	ShapeType GetType()const override;

	bool IsShapeIncludePoint(double x, double y)const override;
};