#pragma once

#include "./IPainter.h"

class Painter : public IPainter
{
public:
	void DrawPicture(const PictureDraft& picture, ICanvas& canvas)override
	{
		for (const auto& shape : picture.GetShapes())
		{
			shape->Draw(canvas);
		}
	}
};