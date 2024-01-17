#pragma once

#include <string>

#include "../../Command/CDocumentCommand.h"

// set text command 
class ReplaceTextDocumentCommand : public CDocumentCommand
{
public:
	ReplaceTextDocumentCommand(std::string& paragraphText, const std::string& newText)
		: m_paragraphText(paragraphText)
		, m_prevText(paragraphText)
		, m_newText(newText)
	{
	}

private:
	void DoExecute()override
	{
		m_paragraphText = m_newText;
	}

	void DoUnexecute()override
	{
		m_paragraphText = m_prevText;
	}

	std::string& m_paragraphText;
	std::string m_prevText;
	std::string m_newText;
};