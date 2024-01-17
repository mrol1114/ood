#pragma once

#include "../Command/ICommand.h"

class ICommandHistory
{
public:
	virtual bool CanUndo() = 0;
	virtual bool CanRedo() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual void ExecuteAndAddCommand(ICommandPtr&& command) = 0;

	virtual ~ICommandHistory() = default;
};

using ICommandHistoryPtr = std::unique_ptr<ICommandHistory>;