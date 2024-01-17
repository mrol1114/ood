#pragma once

#include "../CEllipse.h"
#include "../CTriangle.h"
#include "../CRectangle.h"

class CShapeFactory
{
public:
	static std::shared_ptr<IShape> CreateShape(
		ShapeType type, CFrame frame, ICommandHistory& history)
	{
		switch (type)
		{
		case ShapeType::Ellipse:
			return std::make_unique<CEllipse>(frame, history);
		case ShapeType::Triangle:
			return std::make_unique<CTriangle>(frame, history);
		case ShapeType::Rectangle:
			return std::make_unique<CRectangle>(frame, history);
		}
	}
};