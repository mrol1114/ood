#pragma once

#include <memory>

#include "./ICommand.h"
#include "../../shapes/Picture.h"

class ListCommand : public ICommand
{
public:
	ListCommand(std::ostream& output, std::shared_ptr<Picture> picture)
		: m_output(output)
		, m_picture(picture)
	{
	}

	void Execute() override
	{
		unsigned int shapeNumber = 0;

		for (const auto& id: m_picture->GetIds())
		{
			m_output << ++shapeNumber << " " << GetShapeName(m_picture->GetShape(id)->GetType()) << " "
				<< " " << id << " " << m_picture->GetShape(id)->GetColor() << " "
				<< m_picture->GetShape(id)->GetDrawInfo() << std::endl;
		}
	}

private:
	std::string GetShapeName(ShapeType shapeType)
	{
		for (const auto& [name, type] : m_picture->ShapeNameToType)
		{
			if (shapeType == type)
			{
				return name;
			}
		}
	}

	std::shared_ptr<Picture> m_picture;
	std::ostream& m_output;
};