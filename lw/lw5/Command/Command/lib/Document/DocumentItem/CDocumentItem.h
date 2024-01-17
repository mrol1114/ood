#pragma once

#include <iostream>

#include "./Image/IImage.h"
#include "./Paragraph/IParagraph.h"

/*
Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(IImagePtr image, IParagraphPtr paragraph)
	{
		if (image && paragraph)
		{
			throw std::logic_error("DocumentItem must contain image or paragraph, not both");
		}

		m_image = std::move(image);
		m_paragraph = std::move(paragraph);
	}

	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	const IImagePtr& GetImage()const
	{
		return m_image;
	}
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	const IParagraphPtr& GetParagraph()const
	{
		return m_paragraph;
	}

	virtual ~CConstDocumentItem() = default;

protected:
	IImagePtr& DoGetImage()
	{
		return m_image;
	}

	IParagraphPtr& DoGetParagraph()
	{
		return m_paragraph;
	}

private:
	IImagePtr m_image = nullptr;
	IParagraphPtr m_paragraph = nullptr;
};

/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(IImagePtr image, IParagraphPtr paragraph)
		: CConstDocumentItem(std::move(image), std::move(paragraph))
	{

	}
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	IImagePtr& GetImage()
	{
		return DoGetImage();
	}
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	IParagraphPtr& GetParagraph()
	{
		return DoGetParagraph();
	}
};

