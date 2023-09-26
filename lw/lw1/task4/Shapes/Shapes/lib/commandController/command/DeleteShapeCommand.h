#pragma once

#include <memory>

#include "./ICommand.h"
#include "../../shapes/Picture.h"

class DeleteShapeCommand: public ICommand 
{
public:
	DeleteShapeCommand(std::istream& input, std::shared_ptr<Picture> picture)
		: m_input(input)
		, m_picture(picture)
	{
	}

	void Execute() override
	{
		std::string id;
		m_input >> id;

		m_picture->DeleteShape(id);
	}

private:
	std::shared_ptr<Picture> m_picture;
	std::istream& m_input;
};