#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../ConsoleController.h"
#include "../../Document/IDocument.h"

class ListCommand : public CConsoleCommand
{
public:
	ListCommand(IDocumentPtr& document, std::ostream& output)
		: m_document(document)
		, m_output(output)
	{
	}

private:
	void DoExecute()override
	{
		for (size_t index = 0; index < m_document->GetItemsCount(); index++)
		{
			auto item = m_document->GetItem(index);
			m_output << index + 1 << ". ";
			if (item.GetImage())
			{
				m_output << "Image: " << item.GetImage()->GetWidth() << " "
					<< item.GetImage()->GetHeight() << " "
					<< item.GetImage()->GetPath();
			}
			else
			{
				m_output << "Paragraph: " << item.GetParagraph()->GetText();
			}
			m_output << std::endl;
		}
	}

	IDocumentPtr m_document;
	std::ostream& m_output;
};