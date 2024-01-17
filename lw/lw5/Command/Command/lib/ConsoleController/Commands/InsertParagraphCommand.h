#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class InsertParagraphCommand : public CConsoleCommand
{
public:
	InsertParagraphCommand(std::istream& input, IDocumentPtr& document)
		: m_input(input)
		, m_document(document)
	{
	}

private:
	void DoExecute()override
	{
		std::string strPos;
		m_input >> strPos;

		std::optional<size_t> position = std::nullopt;

		if (strPos != m_END_POS)
		{
			position = static_cast<size_t>(std::stoull(strPos));
		}

		std::string text;
		getline(m_input, text);

		m_document->InsertParagraph(text, position);
	}

	inline static const std::string m_END_POS = "end";

	std::istream& m_input;
	IDocumentPtr m_document;
};