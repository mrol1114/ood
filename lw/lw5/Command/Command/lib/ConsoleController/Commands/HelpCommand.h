#pragma once

#include <map>

#include "../../Command/CConsoleCommand.h"

class HelpCommand : public CConsoleCommand
{
public:
	HelpCommand(std::ostream& output,
		const std::map<std::string, ConsoleControllerItem>& controllerCommands)
		: m_controllerCommands(controllerCommands)
		, m_output(output)
	{
	}

private:
	void DoExecute()override
	{
		unsigned int i = 1;
		for (const auto& [shortCut, item] : m_controllerCommands)
		{
			m_output << i++ << ". " << shortCut << item.description << std::endl;
		}
	}

	const std::map<std::string, ConsoleControllerItem>& m_controllerCommands;
	std::ostream& m_output;
};