#pragma once

#include "../../Command/CCommand.h"
#include "../../Shape/IShape.h"
#include "./PictureCommandType.h"

class SetCurrShapeCommand : public CCommand
{
public:
	SetCurrShapeCommand(std::shared_ptr<IShape>& currShape, std::shared_ptr<IShape> newCurrShape)
		: CCommand(PictureCommandType::SET_CURR_SHAPE)
		, m_currShape(currShape)
		, m_prevCurrShape(currShape)
		, m_newCurrShape(newCurrShape)
	{
	}

private:
	void DoExecute()override
	{
		m_currShape = m_newCurrShape;
	}

	void DoUnexecute()override
	{
		m_currShape = m_prevCurrShape;
	}

	bool Replace(ICommand* command)override
	{
		return GetType() == command->GetType();
	}

	std::shared_ptr<IShape>& m_currShape;
	std::shared_ptr<IShape> m_prevCurrShape;
	std::shared_ptr<IShape> m_newCurrShape;
};