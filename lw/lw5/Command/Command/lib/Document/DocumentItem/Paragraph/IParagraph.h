#pragma once

#include <string>
#include <memory>

class IParagraph
{
public:
	virtual const std::string& GetText()const = 0;
	virtual void SetText(const std::string& text) = 0;
	virtual ~IParagraph() = default;
};

using IParagraphPtr = std::shared_ptr<IParagraph>;