#pragma once

#include <fstream>

#include "./IFileServices.h"

class CFileServices : public IFileServices
{
public:
	void CreateDirectoryIfNotExists(const std::string& directoryName)override
	{
		if (!std::filesystem::is_directory(directoryName)
			|| !std::filesystem::exists(directoryName))
		{
			std::filesystem::create_directory(directoryName);
		}
	}

	void CopyFile(
		const std::filesystem::path& fromPath,
		const std::filesystem::path& toPath
	)override
	{
		try
		{
			std::ofstream(toPath, std::ios::binary) 
				<< std::ifstream(fromPath, std::ios::binary).rdbuf();
		}
		catch (std::exception& ex)
		{
			throw std::runtime_error(
				"Could not copy file " + fromPath.string() + " to " + toPath.string()
			);
		}
	}

	void DeleteFile(const std::filesystem::path& pathToFile)override
	{
		try
		{
			std::remove(pathToFile.string().c_str());
		}
		catch (std::exception& ex)
		{
			throw std::runtime_error("Could not delete file");
		}
	}
};