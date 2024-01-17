#pragma once

#include <iostream>

#include "./Image/IImage.h"
#include "./Paragraph/IParagraph.h"

/*
������������ ������� ���������
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

	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	const IImagePtr& GetImage()const
	{
		return m_image;
	}
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
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
������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(IImagePtr image, IParagraphPtr paragraph)
		: CConstDocumentItem(std::move(image), std::move(paragraph))
	{

	}
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	IImagePtr& GetImage()
	{
		return DoGetImage();
	}
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	IParagraphPtr& GetParagraph()
	{
		return DoGetParagraph();
	}
};

