#pragma once

#include <iostream>

#include "../ICommand.h"

#include "../../Shape/Factory/CShapeFactory.h"
#include "../../Slide/ISlide.h"


class AddShapeCommand : public ICommand
{
public:
	AddShapeCommand(ISlide& slide, std::istream& input)
		: m_slide(slide)
		, m_input(input)
	{
	}

	void Execute()override
	{
		std::string strPos;
		m_input >> strPos;

		std::optional<size_t> position = std::nullopt;
		if (strPos != "end")
		{
			position = static_cast<size_t>(std::stoull(strPos));
		}

		std::string shapeDescr;
		std::getline(m_input, shapeDescr);

		m_slide.InsertShape(CShapeFactory::CreateShape(shapeDescr), position);
	}

private:
	ISlide& m_slide;
	std::istream& m_input;
};