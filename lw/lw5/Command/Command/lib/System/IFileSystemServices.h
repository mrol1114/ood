#pragma once

#include <filesystem>
#include <string>
#include <memory>

class IFileSystemServices
{
public:
	virtual void CreateDirectoryIfNotExists(const std::string& directoryName) = 0;

	virtual void CopyFileByPath(
		const std::filesystem::path& fromPath,
		const std::filesystem::path& toPath
	) = 0;

	virtual void DeleteFileByPath(
		const std::filesystem::path& pathToFile
	) = 0;

	virtual void WriteToFile(const std::filesystem::path& path, const std::string& text) = 0;

	virtual ~IFileSystemServices() = default;
};

using IFileSystemServicesPtr = std::shared_ptr<IFileSystemServices>;