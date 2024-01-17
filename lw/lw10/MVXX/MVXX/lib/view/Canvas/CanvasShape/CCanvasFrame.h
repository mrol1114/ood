#pragma once

#include <wx/wx.h>

struct CCanvasFrame
{
	CCanvasFrame(wxRealPoint pos, wxDouble width, wxDouble height)
		: pos(pos)
		, width(width)
		, height(height)
	{
	}

	wxRealPoint pos;
	wxDouble width;
	wxDouble height;
};