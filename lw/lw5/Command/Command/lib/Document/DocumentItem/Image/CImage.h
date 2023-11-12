#pragma once

#include <filesystem>
#include <fstream>

#include "./IImage.h"

class CImage : public IImage
{
public:
	CImage(const std::string& path, unsigned int width, unsigned int height)
		: m_pathToFile(path)
		, m_width(width)
		, m_height(height)
	{
		m_relativePathToCopiedFile.assign(m_IMAGE_FOLDER_NAME);
		m_relativePathToCopiedFile.replace_filename(m_pathToFile.filename());
	}

	const std::filesystem::path& GetPath()const override
	{
		return m_relativePathToCopiedFile;
	}

	unsigned int GetWidth()const override
	{
		return m_width;
	}

	unsigned int GetHeight()const override
	{
		return m_height;
	}

	void Resize(unsigned int width, unsigned int height)override
	{
		m_width = width;
		m_height = height;
	}

private:
	inline static const std::string m_IMAGE_FOLDER_NAME = "images";

	unsigned int m_width;
	unsigned int m_height;
	std::filesystem::path m_pathToFile;
	std::filesystem::path m_relativePathToCopiedFile;
};