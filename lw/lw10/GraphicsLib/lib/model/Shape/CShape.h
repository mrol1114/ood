#pragma once

#include "./IShape.h"

class CShape : public IShape
{
public:
	CFrame GetFrame()const override
	{
		return m_frame;
	}

	void SetFrame(CFrame frame)override
	{
		m_frame = frame;
	}

protected:
	CFrame m_frame;
};