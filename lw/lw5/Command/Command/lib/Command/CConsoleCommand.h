#pragma once

#include <iostream>

#include "./IConsoleCommand.h"

class CConsoleCommand : public IConsoleCommand
{
public:
	void Execute()override
	{
		if (m_isExecuted)
		{
			throw std::logic_error("Command have been already executed");
		}

		DoExecute();
		m_isExecuted = true;
	}

protected:
	virtual void DoExecute() = 0;

private:
	bool m_isExecuted = false;
};