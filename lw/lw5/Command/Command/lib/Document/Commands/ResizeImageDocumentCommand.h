#pragma once

#include "../../Command/CDocumentCommand.h"
#include "../DocumentItem/Image/IImage.h"

class ResizeImageDocumentCommand : public CDocumentCommand
{
public:
	ResizeImageDocumentCommand(
		unsigned int& imageWidth,
		unsigned int& imageHeight,
		unsigned int newWidth,
		unsigned int newHeight
	)
		: m_imageWidth(imageWidth)
		, m_imageHeight(imageHeight)
		, m_prevWidth(imageWidth)
		, m_prevHeight(imageHeight)
		, m_newWidth(newWidth)
		, m_newHeight(newHeight)
	{
	}

private:
	void DoExecute()override
	{
		m_imageWidth = m_newWidth;
		m_imageHeight = m_newHeight;
	}

	void DoUnexecute()override
	{
		m_imageWidth = m_prevWidth;
		m_imageHeight = m_prevHeight;
	}

	unsigned int& m_imageWidth;
	unsigned int& m_imageHeight;
	unsigned int m_newWidth;
	unsigned int m_newHeight;
	unsigned int m_prevWidth;
	unsigned int m_prevHeight;
};