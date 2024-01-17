#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class SaveCommand : public CConsoleCommand
{
public:
	SaveCommand(std::istream& input, IDocumentPtr& document)
		: m_input(input)
		, m_document(document)
	{
	}

private:
	void DoExecute()override
	{
		std::string path;
		m_input >> path;

		m_document->Save(path);
	}

	std::istream& m_input;
	IDocumentPtr m_document;
};