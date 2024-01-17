#pragma once

#include <list>
#include <optional>

#include "../DocumentItem/CDocumentItem.h"
#include "../DocumentItem/Paragraph/CParagraph.h"
#include "../../Command/CDocumentCommand.h"
#include "../../History/ICommandHistory.h"

class InsertParagraphDocumentCommand : public CDocumentCommand
{
public:
	InsertParagraphDocumentCommand(
		const std::string& text,
		std::list<CDocumentItem>& items,
		ICommandHistory& history,
		std::optional<size_t> position
	)
		: m_documentItems(items)
		, m_itemPos(position)
		, m_insertedItem(CDocumentItem{nullptr, std::make_unique<CParagraph>(text, history)})
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
			m_itemPos = m_documentItems.size() - 1;
		}
	}

	void DoUnexecute()override
	{
		auto it = m_documentItems.begin();
		advance(it, m_itemPos.value());
		m_documentItems.erase(it);
	}

	std::list<CDocumentItem>& m_documentItems;
	std::optional<size_t> m_itemPos;
	CDocumentItem m_insertedItem;
};