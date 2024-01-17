#pragma once

#include "../ICommand.h"
#include "../../Slide/ISlide.h"

class SetFrameCommand : public ICommand
{
public:
	SetFrameCommand(ISlide& slide, std::istream& input)
		: m_slide(slide)
		, m_input(input)
	{
	}

	void Execute()override
	{
		CFrame newFrame;

		std::string strValue;
		m_input >> strValue;

		size_t position = static_cast<size_t>(std::stoull(strValue));

		m_input >> strValue;
		newFrame.SetLeft(std::stod(strValue));
		m_input >> strValue;
		newFrame.SetTop(std::stod(strValue));
		m_input >> strValue;
		newFrame.SetWidth(std::stod(strValue));
		m_input >> strValue;
		newFrame.SetHeight(std::stod(strValue));

		m_slide.GetShapeAtIndex(position)->SetFrame({ newFrame });
	}

private:
	ISlide& m_slide;
	std::istream& m_input;
};