#pragma once

#include "../Canvas/ICanvas.h"
#include "../PictureDraft/PictureDraft.h"

class IPainter
{
public:
	virtual ~IPainter() = default;

	virtual void DrawPicture(const PictureDraft& picture, ICanvas& canvas) = 0;
};