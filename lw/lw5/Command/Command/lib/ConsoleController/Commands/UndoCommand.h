#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class UndoCommand : public CConsoleCommand
{
public:
	UndoCommand(IDocumentPtr& document)
		: m_document(document)
	{
	}

private:
	void DoExecute()override
	{
		m_document->Undo();
	}

	IDocumentPtr m_document;
};