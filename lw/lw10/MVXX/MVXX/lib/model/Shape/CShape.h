#pragma once

#include "./IShape.h"
#include "../History/ICommandHistory.h"
#include "../Picture/Command/SetShapeFrameCommand.h"

class CShape : public IShape
{
public:
	CFrame GetFrame()const override
	{
		return m_frame;
	}

	void SetFrame(CFrame frame)override
	{
		m_history.ExecuteAndAddCommand(std::make_unique<SetShapeFrameCommand>(
			m_frame, frame
		));
	}

protected:
	CShape(CFrame frame, ICommandHistory& history)
		: m_frame(frame)
		, m_history(history)
	{
	}

	CFrame m_frame;
	ICommandHistory& m_history;
};