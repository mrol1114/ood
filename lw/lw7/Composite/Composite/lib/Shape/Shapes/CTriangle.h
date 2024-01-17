#pragma once

#include "../CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(CFrame frame)
		: CShape(frame)
	{
	}

	std::string GetShapeName()const override
	{
		return "Triangle";
	}

private:
	void DrawShape(ICanvas& canvas)const override
	{
		const auto& frame = GetFrame();

		canvas.BeginPath();
		canvas.MoveTo({ frame.GetLeft(), frame.GetTop() + frame.GetHeight() });
		canvas.LineTo({ frame.GetLeft() + frame.GetWidth() / 2, frame.GetTop() });
		canvas.LineTo({ frame.GetLeft() + frame.GetWidth(), frame.GetTop() + frame.GetHeight() });
		canvas.LineTo({ frame.GetLeft(), frame.GetTop() + frame.GetHeight() });
		canvas.EndPath();
	}
};