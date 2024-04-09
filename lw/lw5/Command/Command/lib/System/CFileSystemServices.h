#pragma once

#include <fstream>

#include "./IFileSystemServices.h"

class CFileSystemServices : public IFileSystemServices
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

	void CopyFileByPath(
		std::filesystem::path fromPath,
		std::filesystem::path toPath
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

	void DeleteFileByPath(std::filesystem::path pathToFile)override
	{
		try
		{
			std::remove(pathToFile.string().c_str());
		}
		catch (std::exception const& ex)
		{
			throw std::runtime_error("Could not delete file");
		}
	}

	void WriteToFile(std::filesystem::path path, const std::string& text)override
	{
		std::ofstream outFile(path);
		outFile << text;
		outFile.close();
	}
};