#pragma once

#include <iostream>

#include "../ICommand.h"
#include "../../Slide/ISlide.h"

class DisableLineStyleCommand : public ICommand
{
public:
	DisableLineStyleCommand(ISlide& slide, std::istream& input)
		: m_slide(slide)
		, m_input(input)
	{
	}

	void Execute()override
	{
		std::string strPos;
		m_input >> strPos;

		size_t position = static_cast<size_t>(std::stoull(strPos));

		m_slide.GetShapeAtIndex(position)->GetLineStyle()->Enable(false);
	}

private:
	ISlide& m_slide;
	std::istream& m_input;
};