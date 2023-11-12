#pragma once

#include <string>
#include <memory>

#include "./IDesigner.h"
#include "../PictureDraft/PictureDraft.h"
#include "../Shape/Factory/IShapeFactory.h"

class Designer : public IDesigner
{
public:
	Designer(ShapeFactoryPtr&& factory)
		: m_factory(std::move(factory))
	{
	}

	std::unique_ptr<PictureDraft> CreateDraft(std::istream& stream)override
	{
		std::unique_ptr<PictureDraft> draft = std::make_unique<PictureDraft>();
		std::string shapeDescr;

		while (std::getline(stream, shapeDescr))
		{
			draft->Addshape(m_factory->CreateShape(shapeDescr));
		}

		return draft;
	}

private:
	ShapeFactoryPtr m_factory;
};