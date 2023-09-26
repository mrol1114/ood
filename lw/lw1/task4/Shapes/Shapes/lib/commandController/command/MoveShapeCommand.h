#pragma once

#include "./ICommand.h"
#include "../../shapes/Picture.h"

class MoveShapeCommand : public ICommand
{
public:
	MoveShapeCommand(std::istream& input, std::shared_ptr<Picture> picture)
		: m_input(input)
		, m_picture(picture)
	{
	}

	void Execute() override
	{
		std::string id;
		double dx, dy;
		m_input >> id >> dx >> dy;

		m_picture->GetShape(id)->Move(dx, dy);
	}

private:
	std::shared_ptr<Picture> m_picture;
	std::istream& m_input;
};