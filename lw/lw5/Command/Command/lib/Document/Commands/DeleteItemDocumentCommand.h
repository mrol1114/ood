#pragma once

#include <list>
#include <optional>

#include "../DocumentItem/CDocumentItem.h"
#include "../../Command/CCommand.h"
#include "../../System/IFileServices.h"

class DeleteItemDocumentCommand : public CCommand
{
public:
	DeleteItemDocumentCommand()
	{

	}

	~DeleteItemDocumentCommand()
	{
		if (IsExecuted() && m_deletedItem.GetImage())
		{
			m_fileServices->DeleteFile(m_deletedItem.GetImage()->GetPath());
		}
	}

private:
	void DoExecute()override
	{
		auto it = m_documentItems.begin();
		advance(it, m_index);
		m_deletedItem = *it;
		m_documentItems.erase(it);
	}

	void DoUnexecute()override
	{
		if (m_index == m_documentItems.size())
		{
			auto it = m_documentItems.begin();
			advance(it, m_index);
			m_documentItems.insert(it, m_deletedItem);
		}
		else
		{
			m_documentItems.push_back(m_deletedItem);
		}
	}

	std::list<CDocumentItem>& m_documentItems;
	size_t m_index;
	CDocumentItem m_deletedItem;
	PtrIFileServices m_fileServices;
};