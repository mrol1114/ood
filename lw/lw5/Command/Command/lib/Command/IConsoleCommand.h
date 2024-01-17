#pragma once

class IConsoleCommand
{
public:
	virtual void Execute() = 0;
};

using IConsoleCommandPtr = std::unique_ptr<IConsoleCommand>;