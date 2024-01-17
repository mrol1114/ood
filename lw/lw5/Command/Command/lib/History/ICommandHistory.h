#pragma once

#include "../Command/IDocumentCommand.h"

class ICommandHistory
{
public:
	virtual bool CanUndo() = 0;
	virtual bool CanRedo() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual void ExecuteAndAddCommand(IDocumentCommandPtr&& command) = 0;

	virtual ~ICommandHistory() = default;
};

using ICommandHistoryPtr = std::unique_ptr<ICommandHistory>;