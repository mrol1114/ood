#pragma once

#include <iostream>

#include "../../Slide/ISlide.h"
#include "../ICommand.h"

class SetLineColorCommand : public ICommand
{
public:
	SetLineColorCommand(ISlide& slide, std::istream& input)
		: m_slide(slide)
		, m_input(input)
	{
	}

	void Execute()override
	{
		RGBA color(0, 0, 0, 0);
		std::string strValue;
		unsigned int valueColor;
		uint8_t redColor;
		uint8_t greenColor;
		uint8_t blueColor;
		float alpha;

		m_input >> strValue;
		size_t position = static_cast<size_t>(std::stoull(strValue));

		m_input >> valueColor;
		redColor = static_cast<uint8_t>(valueColor);
		m_input >> valueColor;
		greenColor = static_cast<uint8_t>(valueColor);
		m_input >> valueColor;
		blueColor = static_cast<uint8_t>(valueColor);
		m_input >> alpha;

		m_slide.GetShapeAtIndex(position)->GetLineStyle()->SetColor(
			{ redColor, greenColor, blueColor, alpha }
		);
		m_slide.GetShapeAtIndex(position)->GetLineStyle()->Enable(true);
	}

private:
	ISlide& m_slide;
	std::istream& m_input;
};