#pragma once

#include <filesystem>
#include <string>
#include <memory>

class IFileServices
{
public:
	virtual void CreateDirectoryIfNotExists(const std::string& directoryName) = 0;

	virtual void CopyFile(
		const std::filesystem::path& fromPath,
		const std::filesystem::path& toPath
	) = 0;

	virtual void DeleteFile(
		const std::filesystem::path& pathToFile
	) = 0;

	virtual ~IFileServices() = default;
};

using PtrIFileServices = std::unique_ptr<IFileServices>;