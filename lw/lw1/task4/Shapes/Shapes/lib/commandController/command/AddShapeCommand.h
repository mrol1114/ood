#pragma once

#include <iostream>
#include <memory>

#include "./ICommand.h"
#include "../../shapes/Picture.h"
#include "../../canvas/Color.h"
#include "../../shapes/shape/drawingStrategy/factory/DrawingStrategyFactory.h"

class AddShapeCommand : public ICommand
{
public:
	AddShapeCommand(std::istream& input, std::shared_ptr<Picture> picture)
		: m_input(input)
		, m_picture(picture)
	{
	}

	void Execute() override
	{
		DrawingStrategyFactory drawingStrategyFactory;

		std::string shapeName;
		std::string id;
		Color color;

		m_input >> id;
		m_input >> color;
		m_input >> shapeName;

		auto type = ConvertShapeNameToType(shapeName);
		auto drawingStrategy = drawingStrategyFactory.Create(type, m_input);
		m_picture->AddShape(id, std::make_unique<Shape>(std::move(drawingStrategy), color));
	}

private:
	ShapeType ConvertShapeNameToType(const std::string& shapeName)
	{
		if (!m_picture->ShapeNameToType.contains(shapeName))
		{
			throw std::invalid_argument("");
		}
		else
		{
			return m_picture->ShapeNameToType.at(shapeName);
		}
	}

	std::shared_ptr<Picture> m_picture;
	std::istream& m_input;
};