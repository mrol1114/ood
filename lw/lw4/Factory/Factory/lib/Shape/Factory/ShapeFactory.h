#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <sstream>

#include "./IShapeFactory.h"
#include "../CRectangle.h"
#include "../CRegularPolygon.h"
#include "../CTriangle.h"
#include "../CEllipse.h"
#include "../ShapeType.h"
#include "../../Canvas/Color.h"

class ShapeFactory : public IShapeFactory
{
	struct ShapeParams
	{
		ShapeType shapeType = ShapeType::CRegularPolygon;
		Color color = Color::Black;
		std::vector<double> values;
	};

public:
	ShapePtr CreateShape(const std::string& shapeDescr)override
	{
		auto shapeParams = ParseShapeDescr(shapeDescr);
		EnsurePassedParamsCountMatchedRequired(shapeParams.shapeType, shapeParams.values.size());

		switch (shapeParams.shapeType)
		{
		case ShapeType::CRectangle:
			return std::make_unique<CRectangle>(
				Point{ shapeParams.values[0], shapeParams.values[1] },
				shapeParams.values[2],
				shapeParams.values[3],
				shapeParams.color
			);
		case ShapeType::CTriangle:
			return std::make_unique<CTriangle>(
				Point{ shapeParams.values[0], shapeParams.values[1] },
				Point{ shapeParams.values[2], shapeParams.values[3] },
				Point{ shapeParams.values[4], shapeParams.values[5] },
				shapeParams.color
			);
		case ShapeType::CRegularPolygon:
			return std::make_unique<CRegularPolygon>(
				Point{ shapeParams.values[0], shapeParams.values[1] },
				shapeParams.values[2],
				static_cast<unsigned int>(shapeParams.values[3]),
				shapeParams.color
			);
		case ShapeType::CEllipse:
			return std::make_unique<CEllipse>(
				Point{ shapeParams.values[0], shapeParams.values[1] },
				shapeParams.values[2],
				shapeParams.values[3],
				shapeParams.color
			);
		default:
			throw std::runtime_error("Unknown shape type");
		}
	}

private:
	//  сделать метод статическим и константные данные
	ShapeParams ParseShapeDescr(const std::string& shapeDescr)
	{
		ShapeParams params;
		std::istringstream descrStream(shapeDescr);
		std::string value;

		descrStream >> value;
		params.shapeType = ParseShapeType(value);

		descrStream >> value;
		params.color = ParseShapeColor(value);

		while (descrStream >> value)
		{
			params.values.push_back(std::stod(value));
		}

		return params;
	}

	ShapeType ParseShapeType(const std::string& shapeName)
	{
		if (!m_SHAPE_NAMES.contains(shapeName))
		{
			throw std::runtime_error("Type " + shapeName + " does not exists");
		}
		return m_SHAPE_NAMES.at(shapeName);
	}

	Color ParseShapeColor(const std::string& colorName)
	{
		if (!m_COLOR_NAMES.contains(colorName))
		{
			throw std::runtime_error("Color " + colorName + " does not exists");
		}
		return m_COLOR_NAMES.at(colorName);
	}

	void EnsurePassedParamsCountMatchedRequired(ShapeType type, size_t passedParamsCount)
	{
		if (m_REQUIRED_PARAMS_COUNT.at(type) != passedParamsCount)
		{
			throw std::runtime_error("Passed params count does not match required");
		}
	}

	const std::map<std::string, ShapeType> m_SHAPE_NAMES = {
		{ "rectangle", ShapeType::CRectangle },
		{ "triangle", ShapeType::CTriangle },
		{ "regular-polygon", ShapeType::CRegularPolygon },
		{ "ellipse", ShapeType::CEllipse },
	};

	const std::map<std::string, Color> m_COLOR_NAMES = {
		{ "green", Color::Green },
		{ "red", Color::Red },
		{ "blue", Color::Blue },
		{ "yellow", Color::Yellow },
		{ "pink", Color::Pink },
		{ "black", Color::Black },
	};

	const std::map<ShapeType, size_t> m_REQUIRED_PARAMS_COUNT = {
		{ ShapeType::CEllipse, 4 },
		{ ShapeType::CTriangle, 6 },
		{ ShapeType::CRectangle, 4 },
		{ ShapeType::CRegularPolygon, 4 },
	};
};