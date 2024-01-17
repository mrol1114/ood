#pragma once

#include <sstream>
#include <optional>
#include <vector>
#include <map>

#include "../Shapes/CEllipse.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/ShapeType.h"

class CShapeFactory
{
	struct ShapeParams
	{
		std::optional<ShapeType> shapeType = {};
		CFrame frame;
	};

public:
	static IShapePtr CreateShape(const std::string& shapeDescr)
	{
		auto shapeParams = ParseShapeDescr(shapeDescr);

		switch (shapeParams.shapeType.value())
		{
		case ShapeType::Rectangle:
			return std::make_shared<CRectangle>(shapeParams.frame);
		case ShapeType::Triangle:
			return std::make_shared<CTriangle>(shapeParams.frame);
		case ShapeType::Ellipse:
			return std::make_shared<CEllipse>(shapeParams.frame);
		default:
			throw std::runtime_error("Unknown shape type");
		}
	}

private:
	static ShapeParams ParseShapeDescr(const std::string& shapeDescr)
	{
		ShapeParams params;
		std::istringstream descrStream(shapeDescr);
		std::string value;

		descrStream >> value;
		params.shapeType = ParseShapeType(value);

		descrStream >> value;
		params.frame.SetLeft(ConvertStringToDouble(value));

		descrStream >> value;
		params.frame.SetTop(ConvertStringToDouble(value));

		descrStream >> value;
		params.frame.SetWidth(ConvertStringToDouble(value));

		descrStream >> value;
		params.frame.SetHeight(ConvertStringToDouble(value));

		return params;
	}

	static ShapeType ParseShapeType(const std::string& shapeName)
	{
		if (!m_SHAPE_NAMES.contains(shapeName))
		{
			throw std::runtime_error("Type " + shapeName + " does not exists");
		}
		return m_SHAPE_NAMES.at(shapeName);
	}

	static double ConvertStringToDouble(const std::string& value)
	{
		try
		{
			return std::stod(value);
		}
		catch (...)
		{
			throw std::runtime_error("Invalid value for frame parameters");
		}
	}

	inline static const std::map<std::string, ShapeType> m_SHAPE_NAMES = {
		{ "rectangle", ShapeType::Rectangle },
		{ "triangle", ShapeType::Triangle },
		{ "ellipse", ShapeType::Ellipse },
	};
};