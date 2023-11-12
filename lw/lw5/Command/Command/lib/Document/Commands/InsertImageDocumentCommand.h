#pragma once

#include <list>
#include <optional>

#include "../DocumentItem/CDocumentItem.h"
#include "../../Command/CCommand.h"
#include "../DocumentItem/Image/CImage.h"
#include "../../System/IFileServices.h"

class InsertParagraphDocumentCommand : public CCommand
{
public:
	InsertParagraphDocumentCommand(
		const std::filesystem::path& path,
		int width,
		int height,
		std::optional<size_t> position = std::nullopt,
		std::list<CDocumentItem>& items,
		PtrIFileServices fileServices
	)
		: m_documentItems(items)
		, m_fileServices(std::move(fileServices))
		, m_insertedItem(CDocumentItem{ std::make_unique<CImage>(path, width, height), nullptr })
		, m_relativeImagePath(m_IMAGE_FOLDER_NAME)
	{
		m_relativeImagePath.replace_filename(path.filename());
		m_relativeImagePath.replace_extension(path.extension());

		m_fileServices->CreateDirectoryIfNotExists(m_IMAGE_FOLDER_NAME);
		m_fileServices->CopyFile(path, m_relativeImagePath);
	}

	~InsertParagraphDocumentCommand()
	{
		if (!IsExecuted())
		{
			m_fileServices->DeleteFile(m_relativeImagePath);
		}
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

	inline static const std::string m_IMAGE_FOLDER_NAME = "images";

	std::list<CDocumentItem>& m_documentItems;
	std::optional<size_t> m_itemPos;
	CDocumentItem m_insertedItem;
	PtrIFileServices m_fileServices;
	std::filesystem::path m_relativeImagePath;
};