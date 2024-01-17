#pragma once

#include "../../Command/CCommand.h"
#include "../../Shape/IShape.h"
#include "./PictureCommandType.h"

class AddShapeCommand : public CCommand
{
public:
	AddShapeCommand(std::list<std::shared_ptr<IShape>>& shapes, std::shared_ptr<IShape> shape)
		: CCommand(PictureCommandType::ADD_SHAPE)
		, m_shapes(shapes)
		, m_addedShape(shape)
	{
	}

private:
	void DoExecute()override
	{
		m_shapes.push_front(m_addedShape);
	}

	void DoUnexecute()override
	{
		m_shapes.pop_front();
	}

	std::list<std::shared_ptr<IShape>>& m_shapes;
	std::shared_ptr<IShape> m_addedShape;
};