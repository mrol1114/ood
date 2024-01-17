#pragma once

#include <iostream>

#include "./IDocumentCommand.h"

class CDocumentCommand : public IDocumentCommand
{
public:
	void Execute()override
	{
		if (m_isExecuted)
		{
			throw std::logic_error("Command have been executed already");
		}

		DoExecute();
		m_isExecuted = true;
	}

	void Unexecute()override
	{
		if (!m_isExecuted)
		{
			throw std::logic_error("Command is not executed");
		}

		DoUnexecute();
		m_isExecuted = false;
	}

	virtual void Delete()override
	{
	}

protected:
	virtual void DoExecute() = 0;

	virtual void DoUnexecute() = 0;

	bool IsExecuted()
	{
		return m_isExecuted;
	}

private:
	bool m_isExecuted = false;
};