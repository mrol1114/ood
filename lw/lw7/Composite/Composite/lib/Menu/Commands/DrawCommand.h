#pragma once

#include "../../Slide/ISlide.h"
#include "../../Canvas/ICanvas.h"
#include "../ICommand.h"

class DrawCommand : public ICommand
{
public:
	DrawCommand(ISlide& slide, ICanvas& canvas)
		: m_slide(slide)
		, m_canvas(canvas)
	{
	}

	void Execute()override
	{
		m_canvas.Clear();
		for (size_t index = 0; index < m_slide.GetShapeCount(); index++)
		{
			m_slide.GetShapeAtIndex(index)->Draw(m_canvas);
		}
	}

private:
	ISlide& m_slide;
	ICanvas& m_canvas;
};