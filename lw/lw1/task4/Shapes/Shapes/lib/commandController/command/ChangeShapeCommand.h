#pragma once

#include <iostream>
#include <memory>

#include "./ICommand.h"
#include "../../shapes/Picture.h"
#include "../../canvas/Color.h"
#include "../../shapes/shape/drawingStrategy/factory/ShapeStrategyFactory.h"

class ChangeShapeCommand : public ICommand
{
public:
	ChangeShapeCommand(std::istream& input, std::shared_ptr<Picture> picture)
		: m_input(input)
		, m_picture(picture)
	{
	}

	void Execute() override
	{
		ShapeStrategyFactory shapeStrategyFactory;

		std::string shapeName;
		std::string id;

		m_input >> id;
		m_input >> shapeName;

		auto type = ConvertShapeNameToType(shapeName);
		m_picture->GetShape(id)->SetDrawingStrategy(shapeStrategyFactory.Create(type, m_input));
	}

private:
	ShapeType ConvertShapeNameToType(const std::string& shapeName)
	{
		if (!m_picture->ShapeNameToType.contains(shapeName))
		{
			throw std::invalid_argument("");
		}
		return m_picture->ShapeNameToType.at(shapeName);
	}

	std::shared_ptr<Picture> m_picture;
	std::istream& m_input;
};