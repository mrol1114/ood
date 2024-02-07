#pragma once

#include <cmath>
#include "../Shape/CFrame.h"

class CKeyPoint
{
public:
	CKeyPoint(CFrame frame);

	bool IsShapeIncludePoint(double x, double y)const;

	CFrame GetFrame()const;

	void SetFrame(CFrame frame);

private:
	CFrame m_frame;
};