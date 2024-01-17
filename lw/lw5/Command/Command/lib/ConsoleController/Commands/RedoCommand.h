#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class RedoCommand : public CConsoleCommand
{
public:
	RedoCommand(IDocumentPtr& document)
		: m_document(document)
	{
	}

private:
	void DoExecute()override
	{
		m_document->Redo();
	}

	IDocumentPtr m_document;
};