#pragma once

#include <memory>
#include <string>

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
	virtual bool Replace(ICommand* command) = 0;
	virtual const std::string& GetType()const = 0;

	virtual ~ICommand() = default;
};

using ICommandPtr = std::unique_ptr<ICommand>;