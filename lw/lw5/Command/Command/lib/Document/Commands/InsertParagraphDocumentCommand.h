#pragma once

#include <list>
#include <optional>

#include "../DocumentItem/CDocumentItem.h"
#include "../DocumentItem/Paragraph/CParagraph.h"
#include "../../Command/CCommand.h"

class InsertParagraphDocumentCommand : public CCommand
{
public:
	InsertParagraphDocumentCommand(
		const std::string& text, 
		std::optional<size_t> position, 
		std::list<CDocumentItem>& items)
		: m_documentItems(items)
		, m_itemPos(position)
		, m_insertedItem(CDocumentItem{nullptr, std::make_unique<CParagraph>(text)})
	{
	}

private:
	void DoExecute()override
	{
		if (m_itemPos != std::nullopt)
		{
			auto it = m_documentItems.begin();
			advance(it, m_itemPos.value());
			m_documentItems.insert(it, m_insertedItem);
		}
		else
		{
			m_documentItems.push_back(m_insertedItem);
		}
	}

	void DoUnexecute()override
	{
		if (m_itemPos != std::nullopt)
		{
			auto it = m_documentItems.begin();
			advance(it, m_itemPos.value());
			m_documentItems.erase(it);
		}
		else
		{
			m_documentItems.pop_back();
		}
	}

	std::list<CDocumentItem>& m_documentItems;
	std::optional<size_t> m_itemPos;
	CDocumentItem m_insertedItem;
};