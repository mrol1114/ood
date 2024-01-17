#pragma once

#include <memory>

class IDocumentCommand
{
public:
	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
	virtual void Delete() = 0;

	virtual ~IDocumentCommand() = default;
};

using IDocumentCommandPtr = std::unique_ptr<IDocumentCommand>;