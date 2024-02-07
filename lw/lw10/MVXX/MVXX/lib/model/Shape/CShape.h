#pragma once

#include "./IShape.h"

class CShape : public IShape
{
public:
	CFrame GetFrame()const override;

	void SetFrame(CFrame frame)override;

protected:
	CShape(CFrame frame);

	CFrame m_frame;
};