#pragma once

#include <memory>

#include "./ICommand.h"
#include "../../shapes/Picture.h"

class HelpCommand : public ICommand
{
public:
	HelpCommand(std::ostream& output, const std::unordered_map<std::string, CommandType>& commands)
		: m_output(output)
		, m_commands(commands)
	{
	}

	void Execute() override
	{
		m_output << "Commands:" << std::endl;
		for (const auto& [name, type] : m_commands)
		{
			m_output << name << std::endl;
		}
	}

private:
	std::ostream& m_output;
	std::unordered_map<std::string, CommandType> m_commands;
};