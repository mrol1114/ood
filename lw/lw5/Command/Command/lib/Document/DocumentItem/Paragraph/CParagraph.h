#pragma once

#include "./IParagraph.h"
#include "../../Commands/ReplaceTextDocumentCommand.h"
#include "../../../History/ICommandHistory.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(const std::string& text, ICommandHistory& history)
		: m_text(text)
		, m_history(history)
	{
	}

	const std::string& GetText()const override
	{
		return m_text;
	}

	void SetText(const std::string& text)override
	{
		m_history.ExecuteAndAddCommand(
			std::make_unique<ReplaceTextDocumentCommand>(m_text, text)
		);
	}

private:
	std::string m_text;
	ICommandHistory& m_history;
};