#pragma once

#include "./CCanvasFrame.h"
#include "./CCanvasShapeType.h"

struct CCanvasShape
{
	CCanvasShape(CCanvasFrame frame, CCanvasShapeType type, 
		wxColor fillColor, wxColor strokeColor, bool isFillEnabled, bool isStrokeEnabled)
		: frame(frame)
		, type(type)
		, fillColor(fillColor)
		, strokeColor(strokeColor)
		, isFillEnabled(isFillEnabled)
		, isStrokeEnabled(isStrokeEnabled)
	{
	}

	CCanvasFrame frame;
	CCanvasShapeType type;
	wxColor fillColor;
	wxColor strokeColor;
	bool isFillEnabled;
	bool isStrokeEnabled;
};