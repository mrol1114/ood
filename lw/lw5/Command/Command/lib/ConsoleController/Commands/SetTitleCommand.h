#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class SetTitleCommand : public CConsoleCommand
{
public:
	SetTitleCommand(std::istream& input, IDocumentPtr& document)
		: m_input(input)
		, m_document(document)
	{
	}

private:
	void DoExecute()override
	{
		std::string text;
		getline(m_input, text);

		m_document->SetTitle(text);
	}

	std::istream& m_input;
	IDocumentPtr m_document;
};