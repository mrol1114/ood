#pragma once

#include <iostream>

#include "../../Slide/ISlide.h"
#include "../ICommand.h"

class SetLineWidthCommand : public ICommand
{
public:
	SetLineWidthCommand(ISlide& slide, std::istream& input)
		: m_slide(slide)
		, m_input(input)
	{
	}

	void Execute()override
	{
		std::string strValue;

		m_input >> strValue;
		size_t position = static_cast<size_t>(std::stoull(strValue));

		m_input >> strValue;
		double lineWidth = std::stod(strValue);

		m_slide.GetShapeAtIndex(position)->GetLineStyle()->SetLineWidth(lineWidth);
	}

private:
	ISlide& m_slide;
	std::istream& m_input;
};