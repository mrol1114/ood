#pragma once

#include <memory>

class ICommand
{
public:
	virtual void Execute() = 0;

	virtual void Unexecute() = 0;
};

using ICommandPtr = std::unique_ptr<ICommand>;