#pragma once

#include "../CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(CFrame frame)
		: CShape(frame)
	{
	}

	std::string GetShapeName()const override
	{
		return "Rectangle";
	}

private:
	void DrawShape(ICanvas& canvas)const override
	{
		const auto& frame = GetFrame();

		canvas.BeginPath();
		canvas.MoveTo({ frame.GetLeft(), frame.GetTop() });
		canvas.LineTo({ frame.GetLeft() + frame.GetWidth(), frame.GetTop() });
		canvas.LineTo({ frame.GetLeft() + frame.GetWidth(), frame.GetTop() + frame.GetHeight() });
		canvas.LineTo({ frame.GetLeft(), frame.GetTop() + frame.GetHeight() });
		canvas.LineTo({ frame.GetLeft(), frame.GetTop() });
		canvas.EndPath();
	}
};