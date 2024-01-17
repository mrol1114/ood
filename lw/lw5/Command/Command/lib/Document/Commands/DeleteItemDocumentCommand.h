#pragma once

#include <list>
#include <optional>

#include "../DocumentItem/CDocumentItem.h"
#include "../../Command/CDocumentCommand.h"
#include "../../System/IFileSystemServices.h"

class DeleteItemDocumentCommand : public CDocumentCommand
{
public:
	DeleteItemDocumentCommand(
		std::list<CDocumentItem>& items, size_t index, IFileSystemServicesPtr fileSystemServices
	)
		: m_documentItems(items)
		, m_index(index)
		, m_fileSystemServices(fileSystemServices)
	{
	}

private:
	void DoExecute()override
	{
		auto it = m_documentItems.begin();
		advance(it, m_index);
		m_deletedItem = CDocumentItem(*it);
		m_documentItems.erase(it);
	}

	void DoUnexecute()override
	{
		auto it = m_documentItems.begin();
		advance(it, m_index);
		m_documentItems.insert(it, m_deletedItem);
	}

	void Delete()override
	{
		if (IsExecuted() && m_deletedItem.GetImage())
		{
			m_fileSystemServices->DeleteFileByPath(m_deletedItem.GetImage()->GetPath());
		}
	}

	std::list<CDocumentItem>& m_documentItems;
	size_t m_index;
	CDocumentItem m_deletedItem = {nullptr, nullptr};
	IFileSystemServicesPtr m_fileSystemServices;
};