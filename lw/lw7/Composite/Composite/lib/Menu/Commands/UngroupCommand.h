#pragma once

#include <iostream>

#include "../../Slide/ISlide.h"
#include "../ICommand.h"

class UngroupCommand : public ICommand
{
public:
	UngroupCommand(ISlide& slide, std::istream& input)
		: m_slide(slide)
		, m_input(input)
	{
	}

	void Execute()override
	{
		std::string strPos;
		m_input >> strPos;

		size_t position = static_cast<size_t>(std::stoull(strPos));

		m_slide.Ungroup(position);
	}

private:
	ISlide& m_slide;
	std::istream& m_input;
};