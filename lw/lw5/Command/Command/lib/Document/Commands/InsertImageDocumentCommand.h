#pragma once

#pragma comment(lib, "rpcrt4.lib")
#include <windows.h>
#include <rpc.h>

#include <list>
#include <optional>

#include "../DocumentItem/CDocumentItem.h"
#include "../../Command/CDocumentCommand.h"
#include "../DocumentItem/Image/CImage.h"
#include "../../System/IFileSystemServices.h"
#include "../../History/ICommandHistory.h"

class InsertImageDocumentCommand : public CDocumentCommand
{
public:
	InsertImageDocumentCommand(
		const std::filesystem::path& path,
		int width,
		int height,
		std::list<CDocumentItem>& items,
		IFileSystemServicesPtr fileServices,
		ICommandHistory& history,
		std::optional<size_t> position = std::nullopt
	)
		: m_documentItems(items)
		, m_fileServices(std::move(fileServices))
	{
		std::string id = GenerateUuid();
		m_relativeImagePath = m_IMAGE_FOLDER_NAME + m_LINE_SEPARATOR 
			+ id + path.extension().string();
		m_relativeImagePath = m_relativeImagePath.make_preferred();
		m_insertedItem = CDocumentItem{ std::make_unique<CImage>(
				m_relativeImagePath,
				width,
				height,
				history
			), nullptr};

		m_fileServices->CreateDirectoryIfNotExists(m_IMAGE_FOLDER_NAME);
		m_fileServices->CopyFileByPath(path, m_relativeImagePath);
	}

	// create method delete

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
			m_itemPos = m_documentItems.size();
			m_documentItems.push_back(m_insertedItem);
		}
	}

	void DoUnexecute()override
	{
		auto it = m_documentItems.begin();
		advance(it, m_itemPos.value());
		m_documentItems.erase(it);
	}

	void Delete()override
	{
		if (!IsExecuted())
		{
			m_fileServices->DeleteFileByPath(m_relativeImagePath);
		}
	}

	std::string GenerateUuid()
	{
		UUID uuid;
		UuidCreate(&uuid);
		char* str;
		UuidToStringA(&uuid, (RPC_CSTR*)&str);
		std::string uuidStr(str);
		RpcStringFreeA((RPC_CSTR*)&str);
		return uuidStr;
	}

	inline static const std::string m_LINE_SEPARATOR = R"(/)";
	inline static const std::string m_IMAGE_FOLDER_NAME = "images";

	std::list<CDocumentItem>& m_documentItems;
	std::optional<size_t> m_itemPos;
	CDocumentItem m_insertedItem = {nullptr, nullptr};
	IFileSystemServicesPtr m_fileServices;
	std::filesystem::path m_relativeImagePath = "";
};