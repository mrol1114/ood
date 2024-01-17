#pragma once

#include "../../Command/CCommand.h"
#include "../../Shape/IShape.h"
#include "./PictureCommandType.h"

class SetShapeFrameCommand : public CCommand
{
public:
	SetShapeFrameCommand(CFrame& frame, CFrame newFrame)
		: CCommand(PictureCommandType::SET_SHAPE_FRAME)
		, m_frame(frame)
		, m_prevFrame(frame)
		, m_newFrame(newFrame)
	{
	}

private:
	void DoExecute()override
	{
		m_frame = m_newFrame;
	}

	void DoUnexecute()override
	{
		m_frame = m_prevFrame;
	}

	bool Replace(ICommand* command)override
	{
		return GetType() == command->GetType();
	}

	CFrame& m_frame;
	CFrame m_prevFrame;
	CFrame m_newFrame;
};