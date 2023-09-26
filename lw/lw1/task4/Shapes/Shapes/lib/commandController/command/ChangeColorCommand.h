#pragma once

#include "./ICommand.h"
#include "../../shapes/Picture.h"
#include "../../canvas/Color.h"

class ChangeColorCommand : public ICommand
{
public:
	ChangeColorCommand(std::istream& input, std::shared_ptr<Picture> picture)
		: m_input(input)
		, m_picture(picture)
	{
	}

	void Execute() override
	{
		std::string id, color;
		m_input >> id >> color;

		m_picture->GetShapeById(id)->SetColor(color);
	}

private:
	std::shared_ptr<Picture> m_picture;
	std::istream& m_input;
};