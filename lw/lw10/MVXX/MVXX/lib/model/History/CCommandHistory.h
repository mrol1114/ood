#pragma once

#include <deque>
#include <iostream>

#include "./ICommandHistory.h"

class CCommandHistory : public ICommandHistory
{
public:
	bool CanUndo()override
	{
		return m_nextCommandIndex != 0;
	}

	bool CanRedo()override
	{
		auto i = m_commands.size();
		return m_nextCommandIndex < m_commands.size();
	}

	void Undo()override
	{
		if (!CanUndo())
		{
			throw std::logic_error("Command can not be undone");
		}

		m_commands[--m_nextCommandIndex]->Unexecute();
	}

	void Redo()override
	{
		if (!CanRedo())
		{
			throw std::logic_error("Command can not be redone");
		}

		m_commands[m_nextCommandIndex]->Execute();
		m_nextCommandIndex++;
	}

	void ExecuteAndAddCommand(ICommandPtr&& command)override
	{
		if (m_nextCommandIndex < m_commands.size())
		{
			command->Execute();
			++m_nextCommandIndex;
			m_commands.resize(m_nextCommandIndex);
			m_commands.back() = move(command);
		}
		else
		{
			if (m_commands.empty() || !m_commands.back()->Replace(command.get()))
			{
				m_commands.emplace_back(nullptr);
			}

			try
			{
				command->Execute();
				m_commands.back() = move(command);
				m_nextCommandIndex = m_commands.size();
			}
			catch (...)
			{
				if (!m_commands.back())
				{
					m_commands.pop_back();
				}
				throw;
			}
		}
	}

private:

	static const size_t m_MAXIMUM_HISTORY_SIZE = 10;

	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};