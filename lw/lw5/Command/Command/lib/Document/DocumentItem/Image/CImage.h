#pragma once

#include <filesystem>
#include <fstream>

#include "./IImage.h"
#include "../../../History/ICommandHistory.h"
#include "../../Commands/ResizeImageDocumentCommand.h"

class CImage : public IImage
{
public:
	CImage(
		const std::filesystem::path& path,
		unsigned int width, 
		unsigned int height, 
		ICommandHistory& history
	)
		: m_path(path)
		, m_width(width)
		, m_height(height)
		, m_history(history)
	{
		if (!(m_MIN_VALUE <= width && width <= m_MAX_VALUE)
			|| !(m_MIN_VALUE <= height && height <= m_MAX_VALUE))
		{
			throw std::logic_error("Width and height should be from " + std::to_string(m_MIN_VALUE)
				+ " to " + std::to_string(m_MAX_VALUE));
		}

		m_path = m_path.make_preferred();
	}

	const std::filesystem::path& GetPath()const override
	{
		return m_path;
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
		m_history.ExecuteAndAddCommand(
			std::make_unique<ResizeImageDocumentCommand>(m_width, m_height, width, height)
		);
	}

private:
	inline static const unsigned int m_MIN_VALUE = 1;
	inline static const unsigned int m_MAX_VALUE = 10000;

	unsigned int m_width;
	unsigned int m_height;
	std::filesystem::path m_path;
	ICommandHistory& m_history;
};