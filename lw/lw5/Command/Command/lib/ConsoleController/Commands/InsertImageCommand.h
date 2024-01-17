#pragma once

#include "../../Command/CConsoleCommand.h"
#include "../../Document/IDocument.h"

class InsertImageCommand : public CConsoleCommand
{
public:
	InsertImageCommand(std::istream& input, IDocumentPtr& document)
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

		unsigned int width, height;
		m_input >> width >> height;

		std::filesystem::path path;
		m_input >> path;

		m_document->InsertImage(path, width, height, position);
	}

	inline static const std::string m_END_POS = "end";

	std::istream& m_input;
	IDocumentPtr m_document;
};