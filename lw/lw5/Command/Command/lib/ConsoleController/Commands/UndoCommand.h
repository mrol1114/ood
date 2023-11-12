#pragma once

#include "./ICommand.h"

class UndoCommand : public ICommand
{
public:
	void Execute()override
	{

	}

	void Unexecute()override
	{

	}
};