#pragma once

#include <memory>

#include "./ICommand.h"
#include "../../shapes/Picture.h"

class MovePictureCommand : public ICommand
{
public:
	MovePictureCommand(std::istream& input, std::shared_ptr<Picture> picture)
		: m_input(input)
		, m_picture(picture)
	{
	}

	void Execute() override
	{
		double dx, dy;
		m_input >> dx >> dy;

		for (const auto& id : m_picture->GetIds())
		{
			m_picture->GetShapeById(id)->Move(dx, dy);
		}
	}

private:
	std::shared_ptr<Picture> m_picture;
	std::istream& m_input;
};