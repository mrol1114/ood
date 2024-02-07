#include "./CShapeFactory.h"

#include "../CEllipse.h"
#include "../CTriangle.h"
#include "../CRectangle.h"

std::shared_ptr<IShape> CShapeFactory::CreateShape(ShapeType type, CFrame frame)
{
	switch (type)
	{
	case ShapeType::Ellipse:
		return std::make_unique<CEllipse>(frame);
	case ShapeType::Triangle:
		return std::make_unique<CTriangle>(frame);
	case ShapeType::Rectangle:
		return std::make_unique<CRectangle>(frame);
	}
}