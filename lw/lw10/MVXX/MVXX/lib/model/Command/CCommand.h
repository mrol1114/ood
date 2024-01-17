#pragma once

#include <stdexcept>
#include <string>

#include "./ICommand.h"

class CCommand : public ICommand
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

	virtual bool Replace(ICommand* command)override
	{
		return false;
	}

	const std::string& GetType()const override
	{
		return m_type;
	}

protected:
	CCommand(const std::string& type)
		: m_type(type)
	{
	}

	virtual void DoExecute() = 0;

	virtual void DoUnexecute() = 0;

	bool IsExecuted()
	{
		return m_isExecuted;
	}

private:
	bool m_isExecuted = false;
	std::string m_type;
};