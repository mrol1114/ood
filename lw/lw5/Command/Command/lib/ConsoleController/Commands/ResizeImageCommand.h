#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class ResizeImageCommand : public CConsoleCommand
{
public:
	ResizeImageCommand(std::istream& input, IDocumentPtr& document)
		: m_input(input)
		, m_document(document)
	{
	}

private:
	void DoExecute()override
	{
		size_t index;
		m_input >> index;

		unsigned int width, height;
		m_input >> width >> height;

		m_document->GetItem(index).GetImage()->Resize(width, height);
	}

	std::istream& m_input;
	IDocumentPtr m_document;
};