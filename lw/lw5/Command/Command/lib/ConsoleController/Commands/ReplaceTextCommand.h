#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class ReplaceTextCommand : public CConsoleCommand
{
public:
	ReplaceTextCommand(std::istream& input, IDocumentPtr& document)
		: m_input(input)
		, m_document(document)
	{
	}

private:
	void DoExecute()override
	{
		size_t index;
		m_input >> index;

		std::string text;
		m_input >> text;

		m_document->GetItem(index).GetParagraph()->SetText(text);
	}

	std::istream& m_input;
	IDocumentPtr m_document;
};