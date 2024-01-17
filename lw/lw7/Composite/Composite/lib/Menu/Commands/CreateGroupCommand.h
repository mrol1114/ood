#pragma once

#include <iostream>
#include <vector>

#include "../ICommand.h"
#include "../../Slide/ISlide.h"


class CreateGroupCommand : public ICommand
{
public:
	CreateGroupCommand(ISlide& slide, std::istream& input)
		: m_slide(slide)
		, m_input(input)
	{
	}

	void Execute()override
	{
		std::vector<size_t> indexes;

		std::string valueStr;
		size_t index;

		while (m_input >> index)
		{
			indexes.push_back(index);
		}

		m_slide.CreateGroup(indexes);
	}

private:
	ISlide& m_slide;
	std::istream& m_input;
};