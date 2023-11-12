#pragma once

#include <string>

#include "../../Command/CCommand.h"

class SetTitleDocumentCommand : public CCommand
{
public:
	SetTitleDocumentCommand(std::string& title, const std::string& newTitleValue)
		: m_title(title)
		, m_newTitleValue(newTitleValue)
		, m_prevTitleValue(title)
	{
	}

private:
	void DoExecute()override
	{
		m_title = m_newTitleValue;
	}

	void DoUnexecute()override
	{
		m_title = m_prevTitleValue;
	}

	std::string& m_title;
	std::string m_newTitleValue;
	std::string m_prevTitleValue;
};