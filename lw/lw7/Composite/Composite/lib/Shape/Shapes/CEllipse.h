#pragma once

#include "../CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(CFrame frame)
		: CShape(frame)
	{
	}

	std::string GetShapeName()const override
	{
		return "Ellipse";
	}

private:
	void DrawShape(ICanvas& canvas)const override
	{
		const auto& frame = GetFrame();
		canvas.DrawEllipse(
			frame.GetLeft(), frame.GetTop(), frame.GetWidth() / 2, frame.GetHeight() / 2
		);
	}
};