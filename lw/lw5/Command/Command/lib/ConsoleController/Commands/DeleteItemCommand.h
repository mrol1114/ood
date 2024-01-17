#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class DeleteItemCommand : public CConsoleCommand
{
public:
	DeleteItemCommand(std::istream& input, IDocumentPtr& document)
		: m_input(input)
		, m_document(document)
	{
	}

private:
	void DoExecute()override
	{
		size_t index;
		m_input >> index;

		m_document->DeleteItem(index);
	}

	std::istream& m_input;
	IDocumentPtr m_document;
};