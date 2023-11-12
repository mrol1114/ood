#pragma once

#include <deque>
#include <iostream>

#include "../Command/ICommand.h"

class CCommandHistory
{
public:
	bool CanUndo()
	{
		return m_nextCommandIndex != 0;
	}

	bool CanRedo()
	{
		return m_nextCommandIndex < m_commands.size();
	}

	void Undo()
	{
		if (!CanUndo())
		{
			throw std::logic_error("Command can not be undone");
		}

		m_commands[--m_nextCommandIndex]->Unexecute();
	}

	void Redo()
	{
		if (!CanRedo())
		{
			throw std::logic_error("Command can not be redone");
		}

		m_commands[m_nextCommandIndex - 1]->Execute();
		m_nextCommandIndex++;
	}

	void ExecuteAndAddCommand(ICommandPtr&& command)
	{
		m_commands.push_back(nullptr);

		try
		{
			command->Execute();
			m_commands[m_commands.size() - 1] = std::move(command);
		}
		catch (std::exception& ex)
		{
			m_commands.pop_back();
			throw ex;
		}

		if (m_commands.size() > m_MAXIMUM_HISTORY_SIZE)
		{
			m_commands.pop_front();
		}
	}

private:
	static const size_t m_MAXIMUM_HISTORY_SIZE = 10;

	void ResizeCommandsToCurrentIndex()
	{
		m_commands.resize(m_nextCommandIndex);
	}

	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};