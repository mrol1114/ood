#pragma once

#include "./IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(const std::string& text)
		: m_text(text)
	{
	}

	const std::string& GetText()const override
	{
		return m_text;
	}

	void SetText(const std::string& text)override
	{
		m_text = text;
	}

private:
	std::string m_text;
};